#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

typedef struct Node
{
    Contact *value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List
{
    size_t size;
    Node *head;
    Node *tail;
} List;


List *create_list()
{
    List *tmp = (List *)malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void print_list(List *lst, void (*fun)(void*)) {
	Node *tmp = lst->head;
	while (tmp) {
		fun(tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

void* delete(List *lst, size_t index) {
    Node *elm = NULL;
    void *tmp = NULL;
    elm = get_node(lst, index);
    if (elm == NULL) {
        exit(EXIT_FAILURE);
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;
    if (!elm->prev) {
        lst->head = elm->next;
    }
    if (!elm->next) {
        lst->tail = elm->prev;
    }
    free(elm);
    lst->size--;
    return tmp;
}

void insert(List *lst, size_t index, Contact *value) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = get_Node(lst, index);
    if (elm == NULL) {
        exit(EXIT_FAILURE);
    }
    ins = (Node*) malloc(sizeof(Node));
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;
    if (!elm->prev) {
        lst->head = elm;
    }
    if (!elm->next) {
        lst->tail = elm;
    }
    lst->size++;
}

Node* get_node(List *lst, size_t index) {
    Node *tmp = lst->head;
    size_t i = 0;
    if (index < lst->size/2) {
        i = 0;
        tmp = lst->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = lst->size - 1;
        tmp = lst->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

void delete_list(List **lst)
{
    Node *tmp = (*lst)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*lst);
    (*lst) = NULL;
}

void pop_back(List *lst) {
    Node *next;
    if (lst->tail == NULL) {
        exit(EXIT_FAILURE);
    }
    next = lst->tail;
    lst->tail = lst->tail->prev;
    if (lst->tail) {
        lst->tail->next = NULL;
    }
    if (next == lst->head) {
        lst->head = NULL;
    }
    free(next);
    lst->size--;
}

void pop_front(List *lst) {
    Node *prev;
    if (lst->head == NULL) {
        exit(EXIT_FAILURE);
    }
    prev = lst->head;
    lst->head = lst->head->next;
    if (lst->head) {
        lst->head->prev = NULL;
    }
    if (prev == lst->tail) {
        lst->tail = NULL;
    }
    free(prev);
    lst->size--;
}

void push_front(List *lst, Contact *value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(EXIT_FAILURE);
    }
    tmp->value = value;
    tmp->next = lst->head;
    tmp->prev = NULL;
    if (lst->head) {
        lst->head->prev = tmp;
    }
    if (lst->tail == NULL) {
        lst->tail = tmp;
    }
    lst->head = tmp;
    lst->size++;
}

void push_back(List *lst, Contact *value) {
	Node *tmp = (Node*) malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(EXIT_FAILURE);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = lst->tail;
	if (lst->tail) {
		lst->tail->next = tmp;
    }
    if (lst->head == NULL) {
		lst->head = tmp;
    }
	lst->tail = tmp;
	lst->size++;
}
