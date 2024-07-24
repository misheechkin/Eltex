#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int calculate_square(int length){
    return length*length;
}


int main(int argc, char *argv[]){
    pid_t  pid;

    switch (pid=fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0: 

    default:
        break;
    }
    exit(EXIT_SUCCESS);
}