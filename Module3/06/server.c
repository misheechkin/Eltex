#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>
#include "message.h"
#include <fcntl.h>

#define MSG_TYPE_PROCESS 10


int *client_list;

void signal_handler(int sig) {
    switch (sig)
    {
    case SIGUSR2:
        free(client_list);
        exit(EXIT_SUCCESS);
        break;
    
    case SIGUSR1:
        exit(EXIT_SUCCESS);
        break;

    default:
        break;
    }

}

int main(int argc, char *argv[]){
    int msqid;
    if((msqid = msgget(KEY, IPC_CREAT | 0666 )) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("fork");
        msgctl(msqid, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    case 0:
        int size = 0;
        pid_t identification_parent = getppid();
        pid_t pid;
        message_buf receive_message_group;
        message_buf receive_message_parent;
        switch (pid = fork()) {
        case -1:
            perror("fork");
            msgctl(msqid, IPC_RMID, 0);
            exit(EXIT_FAILURE);
        case 0:
            signal(SIGUSR2,signal_handler);
            for(;;) {
                if(msgrcv(msqid,&receive_message_group,SIZE_MESSAGE,MSG_TYPE_SEND_GROUP,0) < 0) {
                    perror("msgsnd");
                    msgctl(msqid, IPC_RMID, 0);
                    exit(EXIT_FAILURE);
                }
        
                while(1)
                {
                    if(msgrcv(msqid,&receive_message_parent,SIZE_MESSAGE,MSG_TYPE_PROCESS,IPC_NOWAIT) > 0) {
                        size++;
                        client_list = realloc(client_list,size *sizeof(int));
                        client_list[size-1] = atoi(receive_message_parent.mtext);
                    }
                    else
                        break;
                }

                for(int i = 0; i < size; i++) {
                    receive_message_group.mtype = client_list[i];
                    if(msgsnd(msqid,&receive_message_group,strlen(receive_message_group.mtext) + 1, 0) < 0) {
                        perror("msgsnd");
                        msgctl(msqid, IPC_RMID, 0);
                        exit(EXIT_FAILURE);
                    }  
                } 
            }
            break;
        default:
            if(msgrcv(msqid,&receive_message_group,SIZE_MESSAGE,MSG_TYPE_FINISH,0) < 0) {
                kill(identification_parent,SIGUSR1);
                kill(pid,SIGUSR2);
                break;
            }
            break;
        }
        break;
    default:
        signal(SIGUSR1,signal_handler);
        message_buf send_message_child;
        message_buf send_message;
        message_buf receive_message;
        for(;;) {
            if(msgrcv(msqid,&receive_message,SIZE_MESSAGE,MSG_TYPE_IDENTIFICATION,0) < 0) {
                perror("msgsnd");
                msgctl(msqid, IPC_RMID, 0);
                exit(EXIT_FAILURE);
            }

            send_message_child.mtype = MSG_TYPE_PROCESS;
            strcpy(send_message_child.mtext,receive_message.mtext);
            if(msgsnd(msqid,&send_message_child,strlen(send_message_child.mtext) + 1, 0) < 0) {
                perror("msgsnd");
                msgctl(msqid, IPC_RMID, 0);
                exit(EXIT_FAILURE);
            }
            int id = atoi(receive_message.mtext);
            strcpy(send_message.mtext,"Вы успешно подключились к серверу");
            send_message.mtype = id;
            if(msgsnd(msqid,&send_message,strlen(send_message.mtext) + 1, 0) < 0) {
                perror("msgsnd");
                msgctl(msqid, IPC_RMID, 0);
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    msgctl(msqid, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}