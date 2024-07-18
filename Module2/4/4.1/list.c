#include <stdlib.h>
#include "list.h"

Node *insert(Node *head, Contact contact)
{
    Node *new_item;
    Node *tmp = head;
    new_item = malloc(sizeof(Node));
    new_item->contact = contact;

    // Вставка элемента в пустой список
    if (head == NULL)
    {
        new_item->prev = new_item;
        new_item->next = new_item;
        head = new_item;
        return head;
    }
    // Вставка элемента в начало или середину списка
    do
    {
        if (contact_cmp(tmp->contact,new_item->contact)>=0)
        {
            new_item->next = tmp;
            new_item->prev = tmp->prev;
            tmp->prev->next = new_item;
            tmp->prev = new_item;
            if (tmp == head)
                head = new_item;
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    // Вставка элемента в конец списка
    new_item->next = tmp;
    new_item->prev = tmp->prev;
    tmp->prev->next = new_item;
    tmp->prev = new_item;
    return head;
}
Node *delete_contact(Node *head, Contact contact)
{
    Node *tmp = head;
    // Если пытаемся удалить элемент из пустого списка
    if (NULL == head)
    {
        printf("Список пуст!\n");
        return head;
    }
    // Поиск и удаление элемента
    do
    {  
        if (contact_cmp(contact,tmp->contact)==0)
        {
            // Если удаляется единственный элемент списка
            if (tmp->next == tmp->prev)
            {
                free(tmp);
                return NULL;
            } // Перестраиваем связи
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            // Если элемент удаляется из начала списка, изменяем head
            if (tmp == head)
                head = head->next;
            // Удаляем найденный элемент
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    // Если элемент не найден, выводим сообщение
    printf("В списке нет этого контакта!\n");
    return head;
}

Node *delete_list(Node *head)
{
    Node *tmp = head;
    Node *item_remove;
    if (NULL == head) {
        return NULL;
    }
    do {
        item_remove = tmp;
        tmp = tmp->next;
        free(item_remove);
    } while (tmp != head);
    return NULL;
}

void print_list(Node *head)
{
    Node*tmp = head;
    if (NULL == head) {
        printf("Список пуст\n");
        return;
    }
    do {
        print_contact(&(tmp->contact),5);
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}