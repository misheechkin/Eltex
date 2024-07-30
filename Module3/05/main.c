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
      
        int number2 = 0;
        int res;
        int temp = 1;
        char mode[2];
        while ((res = read(fd[0],&number2,sizeof(number))) != 0)
        {
            sleep(1);
            kill(pid,SIGUSR1);
            if(res < 0)
            {
                perror("read");
                close(fd[0]);
                exit(EXIT_FAILURE);
            }
            FILE* fdtxt;
            if(temp)
            {
                mode[0]='w';
                mode[1]='\0';
                temp = 0 ;
            }
            else{
                mode[0]='a';
                mode[1]='\0';
            }
            if((fdtxt = fopen("numbers.txt", mode)) == NULL)
            {
                printf("Не удалось открыть файл");
                close(fd[0]);
                exit(EXIT_FAILURE);
            }   
            fprintf(fdtxt, "%d\n", number2);
            fclose(fdtxt); 
            kill(pid,SIGUSR2);
        }
        close(fd[0]);
        break;
    }
    exit(EXIT_SUCCESS);
}


