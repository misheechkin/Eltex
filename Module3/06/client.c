#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include "message.h"

int main(int argc, char *argv[]){
    srand(time(NULL));
    int msqid;
    if((msqid = msgget(KEY,0)) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    int id =  100 + rand() % 100;
    message_buf send_message;
    message_buf receive_message;

    sprintf(send_message.mtext,"%d",id);
    send_message.mtext[3]='\0';
    send_message.mtype = MSG_TYPE_IDENTIFICATION;
    if(msgsnd(msqid,&send_message,strlen(send_message.mtext) + 1, 0) < 0) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,id,IPC_NOWAIT) < 0) {
            perror("Не удалось подлючиться к серверу");
            exit(EXIT_FAILURE);
    }
    printf("%s\n",receive_message.mtext);
    puts("------------Групповой чат---------------");
    while(1){
        message_buf send_message_group;
        message_buf receive_message_group;
        sleep(3);
        while(1){
            if(msgrcv(msqid,&receive_message_group,SIZE_MESSAGE,id, IPC_NOWAIT) >= 0) {
                printf("> %s\n\n",receive_message_group.mtext);
            }
            else
                break;
        }
        printf("\n\n\tОтправить сообщение в группу: ");
        if (fgets(send_message_group.mtext, SIZE_MESSAGE, stdin) != NULL) {
            if (send_message_group.mtext[strlen(send_message_group.mtext) - 1] == '\n') {
                send_message_group.mtext[strlen(send_message_group.mtext) - 1] = '\0';
            }
        }
        
        if (strcmp(send_message_group.mtext, "q") == 0) {
            send_message_group.mtype = MSG_TYPE_FINISH;
        }
        else {
            send_message_group.mtype = MSG_TYPE_SEND_GROUP;
        }
        if(msgsnd(msqid,&send_message_group,strlen(send_message_group.mtext) + 1, 0) < 0) {
            perror("Сервер остановлен:");
            exit(EXIT_FAILURE);
        }
        if(send_message_group.mtype == MSG_TYPE_FINISH)
            exit(EXIT_SUCCESS);
        

    }
   exit(EXIT_SUCCESS);
}
