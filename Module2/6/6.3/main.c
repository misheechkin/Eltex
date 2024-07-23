#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <dlfcn.h>

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

    void *handle;
    double (*func)(double, double);
    Operation operation[] = {
        {"Сложение"},
        {"Вычитание"},
        {"Деление"},
        {"Умножение"},
    };
    char path[4][20]= {"./lib/lib_Sum.so","./lib/lib_Sub.so","./lib/lib_Div.so","./lib/lib_Mult.so"};
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
        handle = dlopen(path[choice-1], RTLD_LAZY);
        if (!handle)
        {
            fprintf(stderr, "%s\n", dlerror());
            return 1;
        }
        strtok (path[choice-1],"_,.");
        char *temp =strtok (NULL,"_,.");
        operation[choice-1].func = dlsym(handle, temp);
        if(!operation[choice-1].func){
             fprintf(stderr, "%s\n", dlerror());
            return 1;
        }
        printf("Введите количество цифр (1-8)\n");
        scanf("%d", &amount);
        double numbers[amount];
        for (int i = 0; i < amount; i++)
        {
            printf("Цифра %d: ", i + 1);
            scanf("%lf", &numbers[i]);
        }
        switch (amount)
        {
        case 1:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0]));
             dlclose(handle);
            break;
        case 2:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1]));
             dlclose(handle);
            break;
        case 3:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2]));
             dlclose(handle);
            break;
        case 4:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3]));
             dlclose(handle);
            break;
        case 5:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]));
            dlclose(handle);
            break;
        case 6:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]));
             dlclose(handle);
            break;
        case 7:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6]));
            dlclose(handle);
           break;
        case 8:
            printf("%.2lf", Calculate(operation[choice - 1].func, amount, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7]));
             dlclose(handle);
            break;
        default:
            printf("Ошибка! Максимальное количество цифр 8");
             dlclose(handle);
            break;
        }
    }
    return 0;
}
