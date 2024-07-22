#include <stdint.h>

#define MAX_LENGTH 30

typedef struct Node{
    char message[MAX_LENGTH];
	uint8_t priority;
	struct Node *next;
	struct Node *prev;
}Node;

typedef struct Queue {
    int size;
    Node *head;
    Node *tail;
} Queue;


Queue* create_queue();

void delete_queue(Queue **queue);

void enqueue(Queue *queue, char* message, uint8_t priority);

void dequeue_priority(Queue *queue,uint8_t priority);

void dequeue_priority_lower(Queue *queue,uint8_t priority);

void print_queue(Queue *queue);

void dequeue(Queue *queue);