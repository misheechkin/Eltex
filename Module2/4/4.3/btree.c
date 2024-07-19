#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int size = 0;

void ins_btree(Contact contact, btree **node)
{
    if (*node == NULL)
    {
        *node = malloc(sizeof(btree));
        (*node)->left = (*node)->right = NULL;
        (*node)->contact = contact;
        (*node)->contact.id=size++;
        return;
    }
    if (contact_cmp((*node)->contact, contact) > 0)
        ins_btree(contact, &(*node)->left);
    else
        ins_btree(contact, &(*node)->right);
}

void print_btree(btree *node)
{
    if (node == NULL)
        return;
    print_btree(node->left);
    print_contact(&node->contact);
    print_btree(node->right);
}


Contact *get_contact(Contact contact,btree *node) {
    while (node) {
        if (contact_cmp(node->contact,contact)>0) {
            node = node->left;
            continue;
        } else if (contact_cmp(node->contact, contact)<0) {
            node = node->right;
            continue;
        } else {
            return &node->contact;
        }
    }
    return NULL;
}

int delete(Contact contact, btree **node)
{
    btree *t, *up;
    if (*node == NULL)
        return 0; 
    if (contact_cmp((*node)->contact,contact)==0)
    {
        if (((*node)->left == NULL) && ((*node)->right == NULL))
        {
            free(*node);
            *node = NULL;
            printf("Delete List\n");
            return 1;
        }
        if ((*node)->left == NULL)
        {
            t = *node;
            *node = (*node)->right;
            free(t);
            printf("Delete Left = 0\n");
            return 1;
        }

        if ((*node)->right == NULL)
        {
            t = *node;
            *node = (*node)->left;
            free(t);
            printf("Delete Right = 0\n");
            return 1;
        }
        t = (*node)->left;
        while (t->right != NULL)
        {
            up = t;
            t = t->right;
        }
        (*node)->contact= t->contact;
        if (up != (*node))
        {
          
            if (t->left != NULL)
                up->right = t->left;
            else
                up->right = NULL;
        }
        else
            (*node)->left = t->left;
       
        free(t);
        printf("Delete Two\n");
        return 1;
    }
    
    if (contact_cmp((*node)->contact,contact)<0)
        return delete(contact, &(*node)->right);
    return delete(contact, &(*node)->left);
}


void free_tree(btree **node) {
  if(*node!=NULL) {
    free_tree(&(*node)->left);
    free_tree(&(*node)->right);
    free(*node);
  }
}