#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SEM_NAME "/my_sem"

int count_numbers(int n) {
    int numbers = 0;
    if (n / 10 == 0)
        return 1;
    else {
        while (n > 0) {
            n = n / 10;
            numbers += 1;
        }
        return numbers;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1 || argc > 2) {
        printf("Не правильно введен аргумент, введите: <количество случайных чисел>\n");
        exit(EXIT_FAILURE);
    }
    int amount = atoi(argv[1]);
    int fd[2];
    sem_t* semaphore;
    if ((semaphore = sem_open(SEM_NAME, O_CREAT, 0600, 0)) == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            close(fd[0]);
            close(fd[1]);
            exit(EXIT_FAILURE);
        case 0:
            close(fd[0]);
            srand(time(NULL));
            int number = 0;
            int number_of_digits = 0;
            for (int i = 0; i < amount; i++) {
                number = rand();
                if (write(fd[1], &number, sizeof(number)) < 0) {
                    perror("write");
                    close(fd[1]);
                    exit(EXIT_FAILURE);
                }
                if (sem_wait(semaphore) != 0) {
                    perror("sem_close");
                    exit(EXIT_FAILURE);
                }
                FILE* fdtxt1;
                if ((fdtxt1 = fopen("numbers.txt", "r")) == NULL) {
                    printf("Не удалось открыть файл");
                    exit(EXIT_FAILURE);
                }
                fseek(fdtxt1, number_of_digits, SEEK_SET);
                while (fscanf(fdtxt1, "%d", &number) != EOF)
                    printf("%d\n", number);
                fclose(fdtxt1);
                number_of_digits += count_numbers(number) + 1;
            }
            if (sem_close(semaphore) != 0) {
                perror("sem_close");
                exit(EXIT_FAILURE);
            }
            close(fd[1]);
            if (sem_unlink(SEM_NAME) != 0) {
                perror("sem_unlink");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            close(fd[1]);
            int number2 = 0;
            int res;
            int temp = 1;
            char mode[2];
            while ((res = read(fd[0], &number2, sizeof(number))) != 0) {
                if (res < 0) {
                    perror("read");
                    close(fd[0]);
                    exit(EXIT_FAILURE);
                }
                FILE* fdtxt;
                if (temp) {
                    mode[0] = 'w';
                    mode[1] = '\0';
                    temp = 0;
                } else {
                    mode[0] = 'a';
                    mode[1] = '\0';
                }
                if ((fdtxt = fopen("numbers.txt", mode)) == NULL) {
                    printf("Не удалось открыть файл");
                    close(fd[0]);
                    exit(EXIT_FAILURE);
                }
                fprintf(fdtxt, "%d\n", number2);
                fclose(fdtxt);
                if (sem_post(semaphore) != 0) {
                    perror("sem_post");
                    exit(EXIT_FAILURE);
                }
            }
            if (sem_close(semaphore) != 0) {
                perror("sem_close");
                exit(EXIT_FAILURE);
            }
            close(fd[0]);
            break;
    }
    exit(EXIT_SUCCESS);
}
