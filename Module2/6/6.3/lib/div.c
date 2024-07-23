#include <stdio.h>
#include <stdlib.h>

double Div(double a, double b)
{
    if (b == 0)
    {
        printf("Ошибка!! На ноль делить нельзя\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}