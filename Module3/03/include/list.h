#ifndef LIST_H
#define LIST_H

#include "contact.h"

typedef struct Node
{
    Contact contact;
    struct Node *next;
    struct Node *prev;
} Node;

Node *insert(Node *head, Contact contact);

Node *insert_from_file(Node *head, Contact contact);

Node *delete_contact(Node *head, int id);

Node *delete_list(Node *head);

void print_list(Node *head);

Contact *find_contact(Node *head, int index);

#endif