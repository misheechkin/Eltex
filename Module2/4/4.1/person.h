#ifndef PERSON_H
#define PERSON_H

#define MAX_LENGTH_STRING 50

typedef struct Person
{
    char name[MAX_LENGTH_STRING];
    char surname[MAX_LENGTH_STRING];
    char patronymic[MAX_LENGTH_STRING];
}Person;

void person_init(Person *person, char *name, char *surname, char *patronymic);

void person_print(Person *person);

#endif