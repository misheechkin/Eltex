#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MSG_SIZE 1024
#define PORT 1510

void calculate(char *buff, int newsockfd);

double sum(double a, double b) {
    return a + b;
}

double division(double a, double b) {
    if (b == 0)
        return 0;
    return a / b;
}

double multiplication(double a, double b) {
    return a * b;
}

double subtraction(double a, double b) {
    return a - b;
}

typedef struct
{
    const char *name;
    double (*func)(double, double);
} Operation;

int main(int argc, char *argv[]) {
    int sockfd;
    int newsockfd;
    pid_t pid;
    struct sockaddr_in server_addr, client_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("sockfd");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (listen(sockfd, 5) < 0) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    fd_set fds;
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&fds);

    int res;
    char buff[MAX_MSG_SIZE];

    FD_SET(sockfd, &fds);
    int max_fd = sockfd;

    int sel_fds;
    struct timeval delay;
    socklen_t clilen = sizeof(client_addr);

    for (;;) {
        }
    exit(EXIT_SUCCESS);
}

void calculate(char *buff, int newsockfd) {
    Operation operation[] = {
        {"+", sum},
        {"/", division},
        {"*", multiplication},
        {"-", subtraction},
    };
    double a, b, result;
    char temp[2];

    if (sscanf(buff, "%lf %s %lf", &a, temp, &b) < 3) {
        strncpy(buff, "Неправильно введенны даннные\n", MAX_MSG_SIZE);
        if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
            perror("write");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
        return;
    }
    int i = 0;
    while (i < sizeof(operation) / sizeof(operation[0])) {
        if (temp[0] == operation[i].name[0]) {
            result = operation[i].func(a, b);
            break;
        }
        i++;
    }

    if (result == 0 && operation[i].name[0] == '/') {
        strncpy(buff, "На ноль делить нельзя\n", MAX_MSG_SIZE);
        if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
            perror("write");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
        return;
    }
    snprintf(buff, sizeof(buff), "%.2lf", result);
    if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
        perror("write");
        close(newsockfd);
        exit(EXIT_FAILURE);
    }
    return;
}
