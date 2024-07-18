#include <stdio.h>
#include <stdlib.h>
#include "list.h"


Person InputPerson()
{
    Person person;
    char name[MAX_LENGTH_STRING],surname[MAX_LENGTH_STRING],patronymic [MAX_LENGTH_STRING];
    printf("Введите имя: ");
    scanf("%s", name);
    printf("Введите фамилию: ");
    scanf("%s", surname);
    printf("Введите отечество: ");
    scanf("%s", patronymic);
    person_init(&person,name,surname,patronymic);
    return person;
}


int input_id(){
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




int main(){
    Node *head=NULL;
    int tmp = 0;
   for(;;) {
        printf("\n1 - Добавить контакт\t2 - Вывести список контактов\n3 - Удалить контакт\t4 - Редактировать контакт\n5 - Вывести дополнительную информацию о контакте\n6 - Выйти из телефоной книги\n");
        scanf("%d", &tmp);
        switch (tmp)
        {
        case 1:
            Contact contact;
            contact_init(&contact,InputPerson());
            head = insert(head,contact);
            break;
        case 2:
            print_list(head);
            break;
        case 3:
            head = delete_contact(head,input_id());
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            head = delete_list(head);
            return EXIT_SUCCESS;
            break;
        default:
            head = delete_list(head);
            return EXIT_SUCCESS;
            break;
        }
    }
    head = delete_list(head);
    return EXIT_SUCCESS;
}