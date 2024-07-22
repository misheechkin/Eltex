
#define MAX_LENGTH 20

typedef struct {
    char *message[MAX_LENGTH];
	unsigned long priority;
	struct Node *next;
	struct Node *prev;
}Node;

typedef struct Queue {
    int size;
    Node *head;
    Node *tail;
} Queue;