#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MSG_SIZE 500
#define PORT 1510

int flag = 1;

void* recv_message(void* arg) {
    char message[MAX_MSG_SIZE];
    int* sockfd = (int*)arg;
    while (flag) {
        if (recv(*sockfd, message, sizeof(message), 0) < 0) {
            perror("recv");
            close(*sockfd);
            exit(EXIT_FAILURE);
        }
        printf("\nS=>C:%s\n", message);
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    int sockfd;
    pthread_t tid;
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr) < 1) {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&tid, NULL, recv_message, (void*)&sockfd) < 0) {
        perror("pthread_create");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    char message[MAX_MSG_SIZE];
    for (;;) {
        if (fgets(message, MAX_MSG_SIZE, stdin) != NULL) {
            if (message[strlen(message) - 1] == '\n') {
                message[strlen(message) - 1] = '\0';
            }
        }

        if (!strcmp(message, "q")) {
            printf("Выход..");
            flag = 0;
            break;
        }

        if (send(sockfd, message, strlen(message) + 1, 0) < 0) {
            perror("send");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }
    if (pthread_join(tid, NULL) != 0) {
        perror("pthread_join");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}
