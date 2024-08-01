#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

#define SEM_NAME_1 "/my_sem1"
#define SEM_NAME_2 "/my_sem2"

int count_numbers(int n)
{
    int numbers;
    if (n/10==0)
      return 1;
    else
    {
        while (n>0) 
        {  
            n=n/10;
            numbers+=1;
        }
        return numbers;
    }     
}

int main(int argc, char *argv[]){

    exit(EXIT_SUCCESS);
}


