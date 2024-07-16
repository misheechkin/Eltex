#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LENGTH 50

mode_t UpdateMode(mode_t currentMode, char *target, char operation, char *action)
{
    mode_t objectMask = 0;
    mode_t mask = 0;
    for (int i = 0; target[i] != 0; i++)
    {
        if (target[i] == 'a' || target[i] == 'u')
            objectMask |= (S_IRUSR | S_IWUSR | S_IXUSR);
        if (target[i] == 'a' || target[i] == 'g')
            objectMask |= (S_IRGRP | S_IWGRP | S_IXGRP);
        if (target[i] == 'a' || target[i] == 'o')
            objectMask |= (S_IROTH | S_IWOTH | S_IXOTH);
    }
    for (int i = 0; action[i] != 0; i++)
        switch (action[i])
        {
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

    switch (operation)
    {
    case '+':
        currentMode |= mask;
        break;
    case '-':
        currentMode &= ~mask;
        break;
    case '=':
        for (int i = 0; target[i] != 0; i++)
        {
            if (target[i] == 'a')
                currentMode = (currentMode & ~0777) | mask;
            else
            {
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





int main()
{
    struct stat statFile;
    char filename[MAX_LENGTH];
    return EXIT_SUCCESS;
}