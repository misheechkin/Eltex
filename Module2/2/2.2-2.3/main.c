#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

double Sum(double a, double b)
{
    return a + b;
}

double Div(double a, double b)
{
    if (b == 0)
    {
        printf("На ноль делить нельзя");
        exit(EXIT_FAILURE);
    }
    return a / b;
}

double Mult(double a, double b)
{
    return a * b;
}

double Sub(double a, double b)
{
    return a - b;
}

double Calculate(double (*operation)(double, double), int n, ...)
{
    double result = 0.0;
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            result = operation(result, va_arg(args, double));
        else
            result = va_arg(args, double);
    }
    va_end(args);
    return result;
}

typedef struct
{
    const char *name;
    double (*func)(double, double);
} Operation;

int main(void)
{  
        Operation op[] = {
            {"Сложение", Sum}, {"Вычитание", Sub}, {"Деление", Div}, {"Умножение", Mult}, };
        for (int i = 0; i < sizeof(op) / sizeof(op[0]); i++)
            printf("%d. %s\n", i + 1, op[i].name);
        printf("%lf", Calculate(op[2].func, 2, (double)3, (double)6));
     return 0;
}
