#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/file.h"



void save_file(Node *head)
{
    Node *tmp = head;
    int fd = 0;
    if ((fd = open("contacts_list.bin", O_CREAT| O_TRUNC | O_WRONLY, 0700)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(head == NULL){
        close(fd);
        return;
    }
    do
    {
        if (write(fd, &tmp->contact, sizeof(tmp->contact)) < 0)
        {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        tmp = tmp->next;
    } while (tmp != head);
    close(fd);
}