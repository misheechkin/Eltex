#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

int main(int argc, char *argv[]){
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
    if(msgsnd(msqid,&send_message,strlen(send_message.mtext)+1,0) < 0) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    sleep(5);
    if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,id,IPC_NOWAIT) < 0) {
        perror("Не удалось подлючиться к серверу");
        exit(EXIT_FAILURE);
    }
    printf("%s\n",receive_message.mtext);
}
