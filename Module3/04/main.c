#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if (argc == 1 || argc > 2) {
        printf("Не правильно введен аргумент, введите: <количество случайных чисел>\n");
        exit(EXIT_FAILURE);
    }
    int amount = atoi(argv[1]);
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    
    exit(EXIT_SUCCESS);
}