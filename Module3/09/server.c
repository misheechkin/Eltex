#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo"
#define PATHNAME "./server.c"

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(int argc, char *argv[]) {
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    int semid;
    key_t key;
    int fd;
    char string[10];
    union semun arg;
    if ((key = ftok(PATHNAME, 'E')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    if ((semid = semget(key, 2, 0666 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    arg.val = 3;
    if (semctl(semid, 1, SETVAL, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
    printf("Ожидание клиентов\nВведите start для начала работы сервера: ");
    scanf("%s", string);

    if (strcmp(string, "start") != 0) {
        puts("Неверно введенные данные");
        if (unlink(FIFO_NAME) != 0) {
            perror("unlink");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    if ((fd = open(FIFO_NAME, O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (unlink(FIFO_NAME) != 0) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }
    int number = 0;
    int res;
    int temp = 1;
    char mode[2];
    int wait_size = 0;

    while ((res = read(fd, &number, sizeof(number))) != 0) {
        if (res < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        }

    if (close(fd) != 0) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
