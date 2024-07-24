#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LENGTH_STRING 50
#define MAX_AMOUNT_ARGS 10


int main(){
    char input_string[MAX_LENGTH_STRING]={0};
    for(;;) {
        printf(">> ");
        if (fgets(input_string, MAX_LENGTH_STRING, stdin) != NULL) {
            if (input_string[strlen(input_string) - 1] == '\n') {
                input_string[strlen(input_string) - 1] = '\0';
            }
        }
        if (strcmp(input_string, "q") == 0) {
            break;
        }
        char *arg = strtok(input_string," ");
        char *args[MAX_AMOUNT_ARGS]={NULL};
        for(int i = 0; i < MAX_AMOUNT_ARGS && arg!=NULL; i++) {
            args[i] = arg;
            arg = strtok(NULL," ");
        }
      
    }
    exit(EXIT_SUCCESS);
}