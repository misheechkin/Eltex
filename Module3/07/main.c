#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#define QUEUE_NAME "/queue2"
#define MAX_MSG_SIZE 255
#define MAX_MESSAGES 10

int main(){
    mqd_t ds;
    int prio;
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    if ((ds = mq_open(QUEUE_NAME, O_CREAT | O_RDWR,0660, &attr)) == -1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    
    
    if (mq_close(ds) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    

    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}