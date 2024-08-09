#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(70);
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "192.001.01.230", &server_addr.sin_addr.s_addr) < 1) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}