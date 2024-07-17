#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_STRING_LENGTH 32

mode_t update_mode(mode_t currentMode, char *target, char operation, char *action)
{
    mode_t objectMask = 0;
    mode_t mask = 0;
    for (int i = 0; target[i] != 0; i++) {
        if (target[i] == 'a' || target[i] == 'u')
            objectMask |= (S_IRUSR | S_IWUSR | S_IXUSR);
        if (target[i] == 'a' || target[i] == 'g')
            objectMask |= (S_IRGRP | S_IWGRP | S_IXGRP);
        if (target[i] == 'a' || target[i] == 'o')
            objectMask |= (S_IROTH | S_IWOTH | S_IXOTH);
    }
    for (int i = 0; action[i] != 0; i++)
        switch (action[i]) {
        case 'r':
            mask |= objectMask & (S_IRUSR | S_IRGRP | S_IROTH);
            break;
        case 'w':
            mask |= objectMask & (S_IWUSR | S_IWGRP | S_IWOTH);
            break;
        case 'x':
            mask |= objectMask & (S_IXUSR | S_IXGRP | S_IXOTH);
            break;
        default:
            printf("Права доступа введены неправильно\n");
            exit(EXIT_FAILURE);
            break;
        }

    switch (operation) {
    case '+':
        currentMode |= mask;
        break;
    case '-':
        currentMode &= ~mask;
        break;
    case '=':
        for (int i = 0; target[i] != 0; i++) {
            if (target[i] == 'a')
                currentMode = (currentMode & ~0777) | mask;
            else {
                if (target[i] == 'u')
                    currentMode = (currentMode & ~0700) | (mask & 0700);
                if (target[i] == 'g')
                    currentMode = (currentMode & ~0070) | (mask & 0070);
                if (target[i] == 'o')
                    currentMode = (currentMode & ~0007) | (mask & 0007);
            }
        }
        break;
    default:
        printf("Такой операции не существует\n");
        exit(EXIT_FAILURE);
        break;
    }
    return currentMode;
}

void print_mode_binary(mode_t mode)
{
    printf("Битовое представление: ");
    for (int i = 8; i >= 0; i--)
        printf("%u", (mode >> i) & 1);
    printf("\n");
}

void print_mode_letters(mode_t mode)
{
    printf("Буквенное представление: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void print_mode_numbers(mode_t mode)
{
    printf("Цифровое представление: %o\n", mode & 0777);
}

mode_t convert_to_mode(char *string)
{
    mode_t mode = strtoul(string, NULL, 8);
    if (!mode) {
        if (strlen(string) > 9) {
            printf("Вы ввели слишком много прав доступа");
            exit(EXIT_FAILURE);
        }
        int j = 0;
        for (int i = 0; string[i] != 0; i++) {
            if (string[i] == 'r')
                mode |= 0400 >> j;
            if (string[i] == 'w')
                mode |= 0200 >> j;
            if (string[i] == 'x')
                mode |= 0100 >> j;
            if (i == 2 || i == 5)
                j += 3;
        }
    }
    return mode;
}

int input(char *string)
{
    getchar();
    printf("Введите: ");
    if (fgets(string, MAX_STRING_LENGTH, stdin) != NULL) {
        if (string[strlen(string) - 1] == '\n')
            string[strlen(string) - 1] = '\0';
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void change_mode(mode_t *mode)
{
    char access_rights[MAX_STRING_LENGTH], temp[MAX_STRING_LENGTH], action[MAX_STRING_LENGTH], target[MAX_STRING_LENGTH];
    char operation;
    input(temp);
    sscanf(temp, "%s %c %s", target, &operation, action);
    *mode = update_mode(*mode, target, operation, action);
}


int main()
{
    struct stat fileStat;
    char filename[MAX_STRING_LENGTH]={0}, access_rights[MAX_STRING_LENGTH]={0};
    void (*print[3])(mode_t) = {print_mode_binary, print_mode_letters, print_mode_numbers};
    mode_t currentMode = 0;
   
    return EXIT_SUCCESS;
}