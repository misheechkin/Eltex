#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "queue.h"


void input_message(char *message){
    puts("Введите cообщение: ");
    scanf("%s", message);
}

void input_priority(uint8_t *priority){
    puts("Введите приоритет от 0 до 255: ");
    scanf("%" SCNu8, priority);
    if(*priority<0 || *priority>255){
        printf("Вы ввели неверный приоритет\n");
        exit(EXIT_FAILURE);
    }
}


int main()
{
    Queue *queue = create_queue();
    char message[MAX_LENGTH];
    uint8_t priority;
    int tmp = 0;
    for (;;)
    {
        printf("\n1 - Добавить сообщение в очередь\n2 - Вывести очередь\n3 - Извлечь сообщение из очереди\n4 - Извлечь сообщение из очереди с указанием приоритета\n5 - Извлечь сообщение из очереди с приоритетом не ниже заданого\n6 - Выйти из программы\n");
        scanf("%d", &tmp);
        switch (tmp)
        {
        case 1:
            input_message(message);
            input_priority(&priority);
            enqueue(queue, message, priority);
            break;
        case 2:
             print_queue(queue);
             break;
        case 3:
            dequeue(queue);
            break;
        case 4:
            input_priority(&priority);
            dequeue_priority(queue, priority);
            break;
        case 5:
            input_priority(&priority);
             dequeue_priority_lower(queue, priority);
            break;
        case 6:
            delete_queue(&queue);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}