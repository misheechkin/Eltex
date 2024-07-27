#include <stdio.h>
#include <string.h>
#include "include/contact.h"

void contact_init(Contact *contact, Person person)
{
    if (contact == NULL)
        return;
    contact->person = person;
    memset(contact->email, 0, MAX_LENGTH_STRING);
    memset(contact->phone_number, 0, MAX_LENGTH_STRING);
    for (int i = 0; i < MAX_SOCIAL_LIST; i++)
    {
        memset(contact->social_network_list[i].name, 0, MAX_LENGTH_STRING);
    }
    memset(contact->work_info.post, 0, MAX_LENGTH_STRING);
    memset(contact->work_info.workplace, 0, MAX_LENGTH_STRING);
}

void full_print_contact(const Contact *contact)
{
    if (contact == NULL)
        return;
    printf("Id: %d\t", contact->id);
    person_print(&(contact->person));
    printf("Email: %s\t", contact->email);
    printf("Номер: %s\t", contact->phone_number);
    work_info_print(&(contact->work_info));
    for (int i = 0; contact->social_network_list[i].name[0]!='\0'; i++)
    {
       social_network_print(&contact->social_network_list[i]);
    }
    
}

void print_contact(const Contact *contact)
{
    if (contact == NULL)
        return;
    printf("\nId: %d\t", contact->id);
    person_print(&(contact->person));
    printf("Email: %s\t", contact->email);
    printf("Номер: %s", contact->phone_number);
    work_info_print(&(contact->work_info));
}

int contact_cmp(Contact contact1, Contact contact2)
{
    int tmp = strcmp(contact1.person.name, contact2.person.name);
    if (tmp > 0)
        return 1;
    if (tmp == 0)
        return 0;
    return -1;
}

void add_social_network_list(SocialNetwork *social_network_list, SocialNetwork social_network)
{
    for (int i = 0; i < MAX_SOCIAL_LIST; i++)
    {
        if (social_network_list[i].name[0] == '\0')
        {
            social_network_list[i] = social_network;
            return;
        }
    }
    printf("Список соц сетей заполнен!\n");
}

void edit_social_networks(SocialNetwork *social_network_list)
{
    printf("Введите название соц сети которую хотите изменить\n");
    char tmp[MAX_LENGTH_STRING];
    scanf("%s", tmp);
    for (int i = 0; social_network_list[i].name[0] != '\0'; i++)
    {
        if (strcmp(tmp, social_network_list[i].name) == 0)
        {
            int tmp2 = 0;
            printf("1 - Изменить название соц сети\n2 - Изменить имя профиля\n3 - Изменить ссылку\n");
            scanf("%d", &tmp2);
            printf("Введите новое значение: ");
            switch (tmp2)
            {
            case 1:
                scanf("%s", social_network_list[i].name);
                break;
            case 2:
                scanf("%s", social_network_list[i].profile_name);
                break;
            case 3:
                scanf("%s", social_network_list[i].link);
                break;
            default:
                break;
            }
            return;
        }
    }
    printf("Соц сети с таким именем не сущетсвует\n");
}



void edit_contact(Contact *contact)
{
    if (contact != NULL)
    {
        int tmp = 0;
        printf("1 - Изменить имя\n2 - Изменить фамилию\n3 - Изменить отчество\n4 - Изменить email\n5 - Изменить место работы\n6 - Изменить должность\n7 - Изменить социальные сети\n8 - Добавить социальные сети\n9 - Изменить номер телефона\n10 - Выйти\n");
        scanf("%d", &tmp);
        if (tmp != 7 && tmp != 8)
            printf("Введите новое значение: ");
        switch (tmp)
        {
        case 1:
            scanf("%s", contact->person.name);
            break;
        case 2:
            scanf("%s", contact->person.surname);
            break;
        case 3:
            scanf("%s", contact->person.patronymic);
            break;
        case 4:
            scanf("%s", contact->email);
            break;
        case 5:
            scanf("%s", contact->work_info.workplace);
            break;
        case 6:
            scanf("%s", contact->work_info.post);
            break;
        case 7:
            edit_social_networks(contact->social_network_list);
            break;
        case 8:
            add_social_network_list(contact->social_network_list, input_social_network());
            break;
        case 9:
            scanf("%s", contact->phone_number);
            break;
        case 10:
            break;
        default:
            break;
        }
    }
}