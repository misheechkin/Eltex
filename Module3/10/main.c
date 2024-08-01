#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

#define SEM_NAME_1 "/my_sem1"
#define SEM_NAME_2 "/my_sem2"

int count_numbers(int n)
{
    int numbers;
    if (n/10==0)
      return 1;
    else
    {
        while (n>0) 
        {  
            n=n/10;
            numbers+=1;
        }
        return numbers;
    }     
}

int main(int argc, char *argv[]){
    if (argc == 1 || argc > 2) {
         printf("Не правильно введен аргумент, введите: <количество случайных чисел>\n");
         exit(EXIT_FAILURE);
    }
    int amount = atoi(argv[1]);
    int fd[2];
    sem_t* semaphore1;
    sem_t* semaphore2;
    
    if((semaphore1 = sem_open(SEM_NAME_1,O_CREAT,0600,0)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    if((semaphore2 = sem_open(SEM_NAME_2,O_CREAT,0600,1)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
   
    exit(EXIT_SUCCESS);
}


