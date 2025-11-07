#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

void sem_wait(int id){ struct sembuf sb={0,-1,0}; semop(id,&sb,1); }
void sem_signal(int id){ struct sembuf sb={0,1,0}; semop(id,&sb,1); }

int main() {
    key_t key = 1234;
    int shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);
    if (shm_id == -1) { perror("shmget"); exit(1); }

    int *shared = shmat(shm_id, NULL, 0);
    if (shared == (int *)-1) { perror("shmat"); exit(1); }

    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    if (sem_id == -1) { perror("semget"); exit(1); }

    union { int val; } arg; arg.val = 1;
    semctl(sem_id, 0, SETVAL, arg);

    sem_wait(sem_id);
    shared[0] = 3;   // multiple
    shared[1] = 0;   // counter
    sem_signal(sem_id);

    int started = 0;

    while (1) {
        sem_wait(sem_id);
        int m = shared[0];
        int c = ++shared[1];      
        sem_signal(sem_id);

        if (c % m == 0)
            printf("Process 1: Cycle %d – %d is a multiple of %d\n", c, c, m);
        else
            printf("Process 1: Cycle %d\n", c);

        if (!started && c > 100) {
            started = 1;
            if (fork() == 0) {
                execl("./process2_101194310_101299427", "process2_101194310_101299427", NULL);
                perror("execl");
                exit(1);
            }
        }

        if (c > 500) break;
        sleep(1);
    }

    shmdt(shared);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    return 0;
}