#ifndef LIST_H
#define LIST_H

#include "contact.h"

typedef struct Node
{
    Contact contact;
    struct Node *next;
    struct Node *prev;
    size_t size;
} Node;

Node *insert(Node *head, Contact contact);

Node *delete_contact(Node *head, int id);

Node *delete_list(Node *head);

void print_list(Node *head);

#endif