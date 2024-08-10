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

#define MAX_MSG_SIZE 500
#define PORT 1510

int nclients = 0;

void calculate(int);

void printusers() {
    if (nclients) {
        printf("%d Количество подключенных клиентов\n",
               nclients);
    } else {
        printf("Нет никаких подключений\n");
    }
}

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
    socklen_t clilen = sizeof(client_addr);
    for (;;) {
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen)) < 0) {
            perror("accept");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        nclients++;
        printf("IP %s подключился!\n", inet_ntoa(client_addr.sin_addr));
        printusers();
        pid = fork();
        if (pid < 0) {
            perror("fork");
            close(sockfd);
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            close(sockfd);
            calculate(newsockfd);
            close(newsockfd);
            nclients--;
            exit(EXIT_SUCCESS);
        } else
            close(newsockfd);
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}

void calculate(int newsockfd) {
    Operation operation[] = {
        {"+", sum},
        {"/", division},
        {"*", multiplication},
        {"-", subtraction},
    };
    double a, b, result;
    char buff[MAX_MSG_SIZE];
    for (;;) {
        strcpy(buff, "Введите пример (в формате <число><операция><число>)\n");
        if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
            perror("write");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
        if (read(newsockfd, buff, sizeof(buff)) < 1) {
            perror("read");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
        char temp[2];
        if (sscanf(buff, "%lf %s %lf", &a, temp, &b) < 3) {
            if (strcmp(temp, "q") == 0) {
                return;
            }
            strcpy(buff, "Неправильно введенны даннные\n");
            if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
                perror("write");
                close(newsockfd);
                exit(EXIT_FAILURE);
            }
            continue;
        }
        for (size_t i = 0; i < sizeof(operation) / sizeof(*operation); i++) {
            if (strcmp(temp, operation[i].name) == 0) {
                result = operation[i].func(a, b);
                if (result == 0 && strcmp(operation[i].name, "/")) {
                    strcpy(buff, "На ноль делить нельзя\n");
                    if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
                        perror("write");
                        close(newsockfd);
                        exit(EXIT_FAILURE);
                    }
                    continue;
                }
            }
        }
        snprintf(buff, sizeof(buff), "%.2lf", result);
        if (write(newsockfd, buff, strlen(buff) + 1) < 0) {
            perror("write");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }
    }
}