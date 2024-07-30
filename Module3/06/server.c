#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define SIZE_MESSAGE 200
#define KEY 20
#define MSG_TYPE_FINISH 255

typedef struct msgbuf {
    long mtype;
    char mtext[SIZE_MESSAGE];
}message_buf;


void signal_handler(int sig){
   exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]){
    int msqid;
    if((msqid = msgget(KEY, IPC_CREAT | 0666 )) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    int size = 0;
    int *client_list;
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("fork");
        msgctl(msqid, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    case 0:
        signal(SIGUSR1,signal_handler);
        message_buf receive_message_group;
        while(1) {
            if(msgrcv(msqid,&receive_message_group,SIZE_MESSAGE,3,0) < 0) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
            for(int i = 0; i < size; i++) {
                receive_message_group.mtype = client_list[i];
                if(msgsnd(msqid,&receive_message_group,strlen(receive_message_group.mtext)+1,0) < 0) {
                    perror("msgsnd");
                    exit(EXIT_FAILURE);
                }  
            }
        }
        break;
    default:
      message_buf send_message;
        message_buf receive_message;
        while (1) {
            if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,1,0) < 0) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
            size++;
            client_list = (int*)realloc(client_list, size * sizeof(int));
            client_list[size-1] = atoi(receive_message.mtext);
            strcpy(send_message.mtext,"Вы успешно подключились к серверу");
            send_message.mtype = client_list[size-1];
            if(msgsnd(msqid,&send_message,strlen(send_message.mtext)+1,0) < 0) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
            if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,255,IPC_NOWAIT) > 0) {
                kill(pid,SIGUSR1);
                break;
            }
        }
        break;
    }
    free(client_list);
    msgctl(msqid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}