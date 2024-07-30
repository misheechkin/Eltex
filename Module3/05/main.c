#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>



 

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
    switch (pid = fork()) {
    case -1:
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        exit(EXIT_FAILURE);
    case 0:
        close(fd[0]);
       
        close(fd[1]);
       break;
    default:
        close(fd[1]);
      
       
        break;
    }
    exit(EXIT_SUCCESS);
}


