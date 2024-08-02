#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define SEM_NAME_1 "/my_sem1"
#define SEM_NAME_2 "/my_sem2"
#define AMOUNT_READERS 3

static int fd;
static sem_t *semaphore1;
static sem_t *semaphore2;

void free_resources()
{
    if (close(fd) != 0)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (sem_close(semaphore1) != 0 || sem_close(semaphore2) != 0)
    {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    if ((semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0600, 0)) == SEM_FAILED ||
        (semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char string[10];
    printf("Ожидание клиентов\nВведите start для начала работы сервера: ");
    scanf("%s", string);
    if (strcmp(string, "start") != 0)
    {
        puts("Неверно введенные данные");
        if (sem_close(semaphore1) != 0 || sem_close(semaphore2) != 0)
        {
            perror("sem_close");
            exit(EXIT_FAILURE);
        }
        if (unlink(FIFO_NAME) != 0)
        {
            perror("unlink");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    if (sem_unlink(SEM_NAME_1) != 0 || sem_unlink(SEM_NAME_2) != 0)
    {
        perror("sem_unlink");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(FIFO_NAME, O_RDONLY)) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (unlink(FIFO_NAME) != 0)
    {
        perror("unlink");
        exit(EXIT_FAILURE);
    }
    
    int number = 0;
    int res;
    int temp = 1;
    char mode[2];
    int size_sem;

    while ((res = read(fd, &number, sizeof(number))) != 0)
    {
        if (res < 0)
        {
            perror("read");
            free_resources();
            exit(EXIT_FAILURE);
        }
        if (sem_getvalue(semaphore1, &size_sem) == 1)
        {
            perror("sem_getvalue");
            free_resources();
            exit(EXIT_FAILURE);
        }
        int size_sem2 = size_sem;

        while (1)
        {
            if (size_sem == 0)
            {
                break;
            }
            int tmp = size_sem - 1;
            if (sem_wait(semaphore1) != 0)
            {
                perror("sem_close");
                free_resources();
                exit(EXIT_FAILURE);
            }
            if (sem_getvalue(semaphore1, &size_sem) == 1)
            {
                perror("sem_getvalue");
                free_resources();
                exit(EXIT_FAILURE);
            }
            if (tmp != size_sem)
            {
                size_sem2--;
            }
        }
        if (temp != 1)
        {
            for (size_t i = 0; i < AMOUNT_READERS - size_sem2; i++)
            {
                if (sem_post(semaphore2) != 0)
                {
                    perror("sem_close");
                    free_resources();
                    exit(EXIT_FAILURE);
                }
            }
        }
        if (temp)
        {
            mode[0] = 'w';
            mode[1] = '\0';
            temp = 0;
        }
        else
        {
            mode[0] = 'a';
            mode[1] = '\0';
        }
        FILE *fdtxt;
        if ((fdtxt = fopen("numbers.txt", mode)) == NULL)
        {
            perror("fopen");
            free_resources();
            exit(EXIT_FAILURE);
        }
        fprintf(fdtxt, "%d\n", number);
        fclose(fdtxt);
        for (size_t i = 0; i < AMOUNT_READERS; i++)
        {
            if (sem_post(semaphore1) != 0)
            {
                perror("sem_post");
                free_resources();
                exit(EXIT_FAILURE);
            }
        }
    }
    free_resources();
    exit(EXIT_SUCCESS);
}
