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
    int flag = 0;
    if ((shmid = shmget(IPC_PRIVATE, MAX_LEN * sizeof(int), IPC_CREAT | 0666)) == -1) {
        perror("shmid");
        exit(EXIT_FAILURE);
    }
    if ((shmp = shmat(shmid, NULL, 0)) == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        while (flag) {
            int min = shmp[0];
            int max = shmp[0];
            for (size_t i = 0; i < MAX_LEN || shmp[i] == -1; i++) {
                if (shmp[i] > max) {
                    max = shmp[i];
                }
                if (shmp[i] < min) {
                    min = shmp[i];
                }
            }
            shmp[0] = min;
            shmp[1] = max;
        }
        if (shmdt(shmp) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
    } else {
        srand(getppid());
        while (flag) {
            int count = rand() % MAX_LEN + 1;
            int i = 0;
            while (i < count) {
                shmp[i] = rand() % 100;
                i++;
            }
            shmp[i] = -1;
            printf("Минимальное число: %d\n Максимальное число: %d\n", shmp[0], shmp[1]);
        }
    }
}