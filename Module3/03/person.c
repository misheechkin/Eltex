#include <stdio.h>
#include <string.h>
#include "include/person.h"

void person_init(Person *person, char *name, char *surname, char *patronymic)
{
    if (person == NULL)
        return;
    if (name != NULL)
    {
        strcpy(person->name, name);
    }
    if (surname != NULL)
    {
        strcpy(person->surname, surname);
    }
    if (patronymic != NULL)
    {
        strcpy(person->patronymic, patronymic);
    }
}

void person_print(const Person *person)
{
    if (person != NULL)
    {
        printf("Имя: %s\t", person->name);
        printf("Фамилия: %s\t", person->surname);
        printf("Отчество: %s\n", person->patronymic);
    }
}
