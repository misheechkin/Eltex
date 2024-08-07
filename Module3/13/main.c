#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MAX_LEN 256

volatile sig_atomic_t flag = 1;

void sigint_handler(int sig) {
    flag = 0;
}

int main(int argc, char* argv[]) {
    int shm_fd;
    int semid;
    sem_t* semaphore1;
    sem_t* semaphore2;

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    if ((shm_fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666)) == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shm_fd, MAX_LEN * sizeof(int)) != 0) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }
    int* shmp = mmap(NULL, MAX_LEN * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shmp == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    if ((semaphore2 = sem_open("my_sem2", O_CREAT, 0600, 0)) == SEM_FAILED ||
        (semaphore1 = sem_open("my_sem1", O_CREAT, 0600, 0)) == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

      if (sem_close(semaphore1) != 0 || sem_close(semaphore2) != 0) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
    if (munmap(shmp, MAX_LEN * sizeof(int) != 0)) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}