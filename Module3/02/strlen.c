#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char string[100];
    printf("Введите строку: ");
    scanf("%s",string);
    printf("Количество символов: %d",strlen(string));
    exit(EXIT_SUCCESS);
}