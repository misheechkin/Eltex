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
        printf("Ошибка!! На ноль делить нельзя\n");
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
    Operation operation[] = {
        {"Сложение", Sum},
        {"Вычитание", Sub},
        {"Деление", Div},
        {"Умножение", Mult},
    };
    int amount = 0;
    int choice = 0;
    for (;;)
    {
        printf("\n");
        for (int i = 0; i < sizeof(operation) / sizeof(*operation); i++)
            printf("%d. %s\n", i + 1, operation[i].name);
        printf("--------------------------\n");
        printf("10. Выйти из программы\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);
        if (choice == 10)
            break;
        printf("Введите количество цифр (1-8)\n");
        scanf("%d", &amount);
        double numbers[amount];
        for (int i = 0; i < amount; i++){
            printf("Цифра %d: ", i+1);
            scanf("%lf", &numbers[i]);
        }
        switch (amount)
        {
        case 1:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0]));
            break;
        case 2:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1]));
            break;
        case 3:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2]));
            break;
        case 4:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3]));
            break;
        case 5:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]));
            break;
        case 6:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]));
            break;
        case 7:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6]));
            break;
        case 8:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7]));
            break;
        default:
            printf("Ошибка! Максимальное количество цифр 8");
            break;
        }
    }
    return 0;
}
