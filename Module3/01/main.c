#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int calculate_square(int length) {
    return length * length;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Не правильно введены аргументы, введите: <длина стороны квадрата> ... ...\n");
        exit(EXIT_FAILURE);
    }

    int side_lengths[argc-1];
    for (int i = 0; i < argc - 1; i++) {
        side_lengths[i] = atoi(argv[i+1]);
    }

    int half = sizeof(side_lengths)/sizeof(*side_lengths)/2;
    pid_t pid;

    switch (pid = fork()) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        printf("Процесс-потомок: \n");
        for(int i = 0; i < half; i++) {
            printf("Площадь квадрата №%d: %d\n", i+1, calculate_square(side_lengths[i]));
        }
        break;
    default:
        printf("Процесс-родитель: \n");
        for(int i = half; i < sizeof(side_lengths)/sizeof(*side_lengths); i++) {
            printf("Площадь квадрата №%d: %d\n", i+1, calculate_square(side_lengths[i]));
        }
        break;
    }
    
    exit(EXIT_SUCCESS);
}