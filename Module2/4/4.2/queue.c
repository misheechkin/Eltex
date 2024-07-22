#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

Queue *create_queue()
{
    Queue *tmp = malloc(sizeof(Queue));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void delete_queue(Queue **queue)
{
    Node *tmp = (*queue)->head;
    Node *next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*queue);
    (*queue) = NULL;
}

void enqueue(Queue *queue, char *message, uint8_t priority)
{
    Node *new_item = malloc(sizeof(Node));
    new_item->priority = priority;
    strcpy(new_item->message, message);
    if (queue->head == NULL && queue->tail == NULL)
    {
        new_item->next = NULL;
        new_item->prev = NULL;
        queue->head = new_item;
        queue->tail = new_item;
        queue->size++;
        return;
    }
    Node *tmp = queue->head;
    while (tmp)
    {
        if (priority >= tmp->priority)
        {
            new_item->next = tmp;
            new_item->prev = tmp->prev;
            if (tmp->prev)
                tmp->prev->next = new_item;
            tmp->prev = new_item;
            if (!new_item->prev)
                queue->head = new_item;
            queue->size++;
            return;
        }
        tmp = tmp->next;
    }
    queue->tail->next = new_item;
    new_item->prev = queue->tail;
    queue->tail = new_item;
    queue->size++;
}

void dequeue(Queue *queue)
{
    Node *next;
    if (queue->tail == NULL)
    {
        printf("Очередь пуста!\n");
        return;
    }
    next = queue->tail;
    queue->tail = queue->tail->prev;
    if (queue->tail)
    {
        queue->tail->next = NULL;
    }
    if (next == queue->head)
    {
        queue->head = NULL;
    }
    free(next);
    queue->size--;
}

void dequeue_priority(Queue *queue, uint8_t priority)
{
    Node *tmp = NULL;
    if (priority > 127)
    {
        tmp = queue->head;
        while (tmp && priority != tmp->priority)
        {
            tmp = tmp->next;
        }
    }
    else
    {
        tmp = queue->tail;
        while (tmp && priority != tmp->priority)
        {
            tmp = tmp->prev;
        }
    }
    if (!tmp)
    {
        printf("В очереди нет сообщения с таким приоритетом\n");
        return;
    }

    if (tmp->prev)
    {
        tmp->prev->next = tmp->next;
    }
    if (tmp->next)
    {
        tmp->next->prev = tmp->prev;
    }
    if (!tmp->prev)
    {
        queue->head = tmp->next;
    }
    if (!tmp->next)
    {
        queue->tail = tmp->prev;
    }
    free(tmp);
    queue->size--;
}

void dequeue_priority_lower(Queue *queue, uint8_t priority)
{
    Node *tmp = NULL;
    tmp = queue->tail;
    while (tmp && priority < tmp->priority)
    {
        tmp = tmp->prev;
    }
    if (!tmp)
    {
        printf("В очереди нет сообщения с таким приоритетом\n");
        return;
    }

    if (tmp->prev)
    {
        tmp->prev->next = tmp->next;
    }
    if (tmp->next)
    {
        tmp->next->prev = tmp->prev;
    }
    if (!tmp->prev)
    {
        queue->head = tmp->next;
    }
    if (!tmp->next)
    {
        queue->tail = tmp->prev;
    }
    free(tmp);
    queue->size--;
}

void print_queue(Queue *queue)
{
    Node *tmp = queue->head;
    while (tmp)
    {
        printf("Cообщение: %s\n", tmp->message);
        printf("Приоритет: %u\n", tmp->priority);
        printf("-----------------------------\n");
        tmp = tmp->next;
    }
    printf("\n");
}
