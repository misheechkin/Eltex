#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#define QUEUE_NAME_1 "/queue1"
#define QUEUE_NAME_2 "/queue2"
#define MAX_MSG_SIZE 250
#define MAX_MESSAGES 10
#define QUEUE_END 255

void chat(mqd_t ds[2],int index1,int index2) {
    char message[MAX_MSG_SIZE];
    int prio;
    struct mq_attr attr;
    while(1) {
         mq_getattr(ds[index2],&attr);

         for (size_t i = 0; i < attr.mq_curmsgs; i++)
         {
            if (mq_receive(ds[index2],message,MAX_MSG_SIZE,&prio) == -1) {  
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            if(prio == QUEUE_END){
                return;
            }
             printf("> %s\n", message);
         }
        printf("\nОтправить сообщение: ");
        if (fgets(message, MAX_MSG_SIZE, stdin) != NULL) {
            if (message[strlen(message) - 1] == '\n') {
                message[strlen(message) - 1] = '\0';
            }
        }
        if (strcmp(message, "exit") == 0) {
            prio = QUEUE_END;
        }
        else
            prio = 2;
        
        if (mq_send(ds[index1], message, strlen(message) + 1, prio) == -1){
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
        if(prio == QUEUE_END){
            return;
        }
    }
}




int main(int argc, char *argv[]) {
     if (argc == 1 || argc > 2) {
        printf("Не правильно введен аргумент, введите: <номер процесса>\n");
        exit(EXIT_FAILURE);
    }
   
    int number_procces = atoi(argv[1]);
    mqd_t ds[2];
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    
    if ((ds[0] = mq_open(QUEUE_NAME_1, O_CREAT | O_RDWR | O_NONBLOCK , 0660, &attr)) == -1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    if ((ds[1] = mq_open(QUEUE_NAME_2, O_CREAT | O_RDWR | O_NONBLOCK, 0660, &attr)) == -1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    if(number_procces == 1){
        chat(ds,0,1);
    }
    else
        chat(ds,1,0);

    if (mq_close(ds[0]) == -1 || mq_close(ds[1]) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    
    if(number_procces == 1){
        if (mq_unlink(QUEUE_NAME_1) == -1 || mq_unlink(QUEUE_NAME_2) == -1) {
            perror("mq_unlink");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}