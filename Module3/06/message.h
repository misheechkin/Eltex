#define SIZE_MESSAGE 200
#define KEY 20
#define MSG_TYPE_FINISH 255
#define MSG_TYPE_IDENTIFICATION 1
#define MSG_TYPE_SEND_GROUP 3

typedef struct msgbuf {
    long mtype;
    char mtext[SIZE_MESSAGE];
}message_buf;
