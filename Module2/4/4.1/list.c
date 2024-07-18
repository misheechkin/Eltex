#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Node *insert(Node *head, Contact contact)
{
    Node *new_item;
    Node *tmp = head;
    new_item = malloc(sizeof(Node));
    new_item->contact = contact;
    if (head == NULL) {
        new_item->prev = new_item;
        new_item->next = new_item;
        head = new_item;
        ++head->size;
        new_item->contact.id = head->size;
        return head;
    }
    do {
        if (contact_cmp(tmp->contact, new_item->contact) >= 0) {
            new_item->next = tmp;
            new_item->prev = tmp->prev;
            tmp->prev->next = new_item;
            tmp->prev = new_item;
            if (tmp == head)
                head = new_item;
            printf("%d", head->size++);
            ++head->size;
            new_item->contact.id = head->size;
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    new_item->next = tmp;
    new_item->prev = tmp->prev;
    tmp->prev->next = new_item;
    tmp->prev = new_item;
     printf("%d", head->size++);
    ++head->size;
    new_item->contact.id = head->size;
    return head;
}
Node *delete_contact(Node *head, int id)
{
    Node *tmp = head;
    if (NULL == head) {
        printf("Список пуст!\n");
        return head;
    }
    do {
        if (id == tmp->contact.id) {
            if (tmp->next == tmp->prev) {
                free(tmp);
                return NULL;
            } 
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            if (tmp == head)
                head = head->next;
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    printf("В списке нет контакта c таким id!\n");
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
    Node *tmp = head;
    if (NULL == head) {
        printf("Список пуст\n");
        return;
    }
    do {
        print_contact(&(tmp->contact));
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}