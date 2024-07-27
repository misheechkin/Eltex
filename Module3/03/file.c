#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/file.h"

Node *read_file()
{
    Node *head = NULL;
    int fd = 0;
    if ((fd = open("contacts_list.bin", O_CREAT | O_RDONLY, 0700)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int res = -1;
    Contact contact;
    while ((res = read(fd, &contact, sizeof(Contact))) != 0)
    {
        if (res < 0)
        {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }
        head = insert_from_file(head, contact);
    }
    return head;
}

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