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
    switch (pid = fork()) {
    case -1:
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        exit(EXIT_FAILURE);
    case 0:
        srand(time(NULL));
        close(fd[0]);
        int number = 0;
        for(int i = 0; i < amount; i++) {
            number = rand();
            if (write(fd[1],&number,sizeof(number)) < 0)
            {
                perror("write");
                close(fd[1]);
                exit(EXIT_FAILURE);
            }
        }
        close(fd[1]);
        break;
    default:
        close(fd[1]);
        FILE* fdtxt;
        if((fdtxt = fopen("numbers.txt", "w")) == NULL)
        {
            printf("Не удалось открыть файл");
            close(fd[0]);
            exit(EXIT_FAILURE);
            
        }
        int number2 = 0;
        int res;
        while ((res = read(fd[0],&number2,sizeof(number))) != 0)
        {
            if(res < 0)
            {
                perror("read");
                close(fd[0]);
                exit(EXIT_FAILURE);
            }
            printf("%d\n", number2);
            fprintf(fdtxt, "%d\n", number2);
        }
        fclose(fdtxt);
        close(fd[0]);
        break;
    }
    exit(EXIT_SUCCESS);
}