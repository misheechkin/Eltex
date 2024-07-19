#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


int main()
{
    btree *root = NULL;
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
            ins_btree(contact,&root);
            break;
        case 2:
            print_btree(root);
            break;
        case 3:
            printf("Введите ФИО контакта которого надо удалить\n");
            Contact contact3;
            contact_init(&contact3, input_person());
            delete(contact3,&root);
            break;
        case 4:
            printf("Введите ФИО контакта которого изменить\n");
            Contact contact4;
            contact_init(&contact4, input_person());
            edit_contact(get_contact(contact4,root));
            break;
        case 5:
            printf("Введите ФИО контакта для которого вывести дополнительную информацию\n");
            Contact contact2;
            contact_init(&contact2, input_person());
            Contact* current_contact = get_contact(contact2,root);
            full_print_contact(current_contact);
            break;
        case 6:
            free_tree(&root);
            return EXIT_SUCCESS;
            break;
        default:
            free_tree(&root);
            return EXIT_SUCCESS;
            break;
        }
    }
   free_tree(&root);
    return EXIT_SUCCESS;
}