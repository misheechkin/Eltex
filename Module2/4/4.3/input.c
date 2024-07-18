#include <stdio.h>
#include "input.h"


Person input_person()
{
    Person person;
    char name[MAX_LENGTH_STRING], surname[MAX_LENGTH_STRING], patronymic[MAX_LENGTH_STRING];
    printf("Введите имя: ");
    scanf("%s", name);
    printf("Введите фамилию: ");
    scanf("%s", surname);
    printf("Введите отечество: ");
    scanf("%s", patronymic);
    person_init(&person, name, surname, patronymic);
    return person;
}

int input_id()
{
    int id = 0;
    printf("Введите id контакта: ");
    scanf("%d", &id);
    if (id < 1)
    {
        printf("Введен неверный id!\n");
        return -1;
    }
    return id;
}

SocialNetwork input_social_network()
{
    SocialNetwork socialNetwork;
    printf("Введите название соц сети: ");
    scanf("%s", socialNetwork.name);
    printf("Введите имя профиля: ");
    scanf("%s", socialNetwork.profile_name);
    printf("Введите ссылку: ");
    scanf("%s", socialNetwork.link);
    return socialNetwork;
}

