#ifndef BTREE_H
#define BTREE_H

#include "contact.h"


typedef struct btree
{
    Contact contact;
    struct btree *left, *right;
} btree;

void ins_btree(Contact contact, btree **node);

void print_btree(btree *p);

Contact *get_contact(Contact contact,btree *node);

int delete(Contact contact, btree **node);

void free_tree(btree **tree);

#endif