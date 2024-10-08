#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PATHNAME "./server.c"
#define FIFO_NAME "/tmp/my_fifo"

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 3) {
        puts("Не правильно введен аргумент, введите: <количество случайных чисел>");
        exit(EXIT_FAILURE);
    }
    int amount = atoi(argv[1]);
    int semid;
    key_t key;
    int fd;
    srand(getpid());
    if ((key = ftok(PATHNAME, 'E')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if ((semid = semget(key, 0, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(FIFO_NAME, O_WRONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int number = 0;
    int tmp = 0;
    for (int i = 0; i < amount; i++) {
        number = rand() % 100;
        if (write(fd, &number, sizeof(number)) < 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        struct sembuf sb[2] = {
            {0, -1, 0},
            {1, -1, 0}};
        if (semop(semid, sb, 2) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }
        FILE *fdtxt1;
        if ((fdtxt1 = fopen("numbers.txt", "r")) == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        while (fscanf(fdtxt1, "%d", &number) != EOF)
            printf("%d\n", number);
        fclose(fdtxt1);
        puts("----------------------------");
        struct sembuf sb2 = {1, 1, 0};
        if (semop(semid, &sb2, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }
    }

    if (close(fd) != 0) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
