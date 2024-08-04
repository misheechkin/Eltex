#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 256

int main() {
    int shmid;
    int* shmp;

    if ((shmid = shmget(IPC_PRIVATE, MAX_LEN * sizeof(int), IPC_CREAT | 0666)) == -1) {
        perror("shmid");
        exit(EXIT_FAILURE);
    }
    if ((shmp = shmat(shmid, NULL, 0)) == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            exit(EXIT_SUCCESS);
        default:
            srand(getppid());
            int count = rand() * MAX_LEN + 1;
            for (int i = 0; i < count; i++) {
                shmp[i] = rand() % 100;
                printf("%d ", shmp[i]);
            }
    }
}