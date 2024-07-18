#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "contact.h"

typedef struct Node
{
    Contact contact;
    struct Node *next;
    struct Node *prev;
} Node;

Node *insert(Node *head, Contact contact);

Node *delete_contact(Node *head, Contact contact);

Node *delete_list(Node *head);

void print_list(Node *head);

#endif