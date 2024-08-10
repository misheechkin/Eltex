#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MSG_SIZE 500

int main(int argc, char* argv[]) {
    int sockfd;
    char message[MAX_MSG_SIZE];
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(1506);
    server_addr.sin_family = AF_INET;
    struct timeval tv;
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    if (inet_pton(AF_INET, "192.168.1.131", &server_addr.sin_addr.s_addr) < 1) {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}