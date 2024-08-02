#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <errno.h>

#define SEM_NAME_1 "/my_sem1"
#define SEM_NAME_2 "/my_sem2"
#define FIFO_NAME "/tmp/my_fifo"


static int fd;
static sem_t *semaphore1;
static sem_t *semaphore2;


void free_resources()
{
    if (sem_close(semaphore1) != 0 || sem_close(semaphore2) != 0)
    {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }

    if (close(fd) != 0)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 2)
    {
        puts("Не правильно введен аргумент, введите: <количество случайных чисел>");
        exit(EXIT_FAILURE);
    }
    int amount = atoi(argv[1]);
    
    if ((semaphore1 = sem_open(SEM_NAME_1, 0)) == SEM_FAILED ||
        (semaphore2 = sem_open(SEM_NAME_2, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    if ((fd = open(FIFO_NAME, O_WRONLY)) == -1)
    {
        perror("open");
        if (sem_close(semaphore1) != 0 || sem_close(semaphore2) != 0)
        {
            perror("sem_close");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }

    srand(getpid());
    int number = 0;
    int number_of_digits = 0;
    int tmp = 0;

    for (int i = 0; i < amount; i++)
    {
        number = rand() % 100;

        if (write(fd, &number, sizeof(number)) < 0)
        {
            perror("write");
            free_resources();
            exit(EXIT_FAILURE);
        }

        if (tmp)
        {
            if (sem_wait(semaphore2) != 0)
            {
                perror("sem_wait");
                free_resources();
                exit(EXIT_FAILURE);
            }
        }

        if (sem_wait(semaphore1) != 0)
        {
            perror("sem_wait");
            free_resources();
            exit(EXIT_FAILURE);
        }

        tmp = 1;
        FILE *fdtxt1;
        
        if ((fdtxt1 = fopen("numbers.txt", "r")) == NULL)
        {
            perror("fopen");
            free_resources();
            exit(EXIT_FAILURE);
        }
    
        while (fscanf(fdtxt1, "%d", &number) != EOF)
            printf("%d\n", number);
        fclose(fdtxt1);
        puts("----------------------------");
    }

    free_resources();

    exit(EXIT_SUCCESS);
}
