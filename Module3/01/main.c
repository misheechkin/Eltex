#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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
    int *side_lengths = NULL;

    if(!(side_lengths = (int*) malloc(argc-1 * sizeof(int)))){
        printf("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc - 1; i++) {
        side_lengths[i] = atoi(argv[i+1]);
    }

    int half = (argc-1)/2;
    pid_t pid;

    switch (pid = fork()) {
    case -1:
        perror("fork");
        free(side_lengths);
        exit(EXIT_FAILURE);
    case 0:
        printf("Процесс-потомок: \n");
        for(int i = 0; i < half; i++) {
            printf("Площадь квадрата №%d: %d\n", i+1, calculate_square(side_lengths[i]));
        }
        break;
    default:
        printf("Процесс-родитель: \n");
        for(int i = half; i < argc - 1; i++) {
            printf("Площадь квадрата №%d: %d\n", i+1, calculate_square(side_lengths[i]));
        }
        break;
    }
    free(side_lengths);
    exit(EXIT_SUCCESS);
}