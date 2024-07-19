#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main()
{
    Node *head = NULL;
    int tmp = 0;
    for (;;)
    {
        printf("\n1 - Добавить контакт\t2 - Вывести список контактов\n3 - Удалить контакт\t4 - Редактировать контакт\n5 - Вывести дополнительную информацию о контакте\n6 - Выйти из телефоной книги\n");
        scanf("%d", &tmp);
        switch (tmp)
        {
        case 1:
            Contact contact;
            contact_init(&contact, input_person());
            head = insert(head, contact);
            break;
        case 2:
            print_list(head);
            break;
        case 3:
            head = delete_contact(head, input_id());
            break;
        case 4:
            edit_contact(find_contact(head,input_id()));
            break;
        case 5:
            Contact* current_contact = find_contact(head,input_id());
            full_print_contact(current_contact);
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