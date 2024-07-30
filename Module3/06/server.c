#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE_MESSAGE 200
#define KEY 20
#define MSG_TYPE_FINISH 255

typedef struct msgbuf {
    long mtype;
    char mtext[SIZE_MESSAGE];
}message_buf;


int main(int argc, char *argv[]){
    int msqid;
    if((msqid = msgget(KEY, IPC_CREAT | 0666 )) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    message_buf send_message;
    message_buf receive_message;
    int size = 0;
    int *client_list;
    while (1)
    {
       
        if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,1,0) < 0){
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        size++;
        client_list = (int*)realloc(client_list, size * sizeof(int));
        client_list[size-1] = atoi(receive_message.mtext);
        strcpy(send_message.mtext,"Вы успешно подключились к серверу");
        send_message.mtype = client_list[size-1];
        if(msgsnd(msqid,&send_message,strlen(send_message.mtext)+1,0) < 0){
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        

        
    }
    msgctl(msqid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}