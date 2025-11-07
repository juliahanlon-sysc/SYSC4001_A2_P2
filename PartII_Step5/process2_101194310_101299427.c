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
    int shm_id = shmget(key, sizeof(int)*2, 0666);
    if (shm_id == -1) { perror("shmget"); exit(1); }

    int *shared = shmat(shm_id, NULL, 0);
    if (shared == (int *)-1) { perror("shmat"); exit(1); }

    int sem_id = semget(key, 1, 0666);
    if (sem_id == -1) { perror("semget"); exit(1); }

    int last = -1;

    while (1) {
        sem_wait(sem_id);
        int m = shared[0];
        int c = shared[1];        
        int done = (c > 500);
        sem_signal(sem_id);

        if (done) break;

        if (c != last) {          
            if (c % m == 0)
                printf("Process 2: Cycle %d – %d is a multiple of %d\n", c, c, m);
            else
                printf("Process 2: Cycle %d\n", c);
            last = c;
        }

        usleep(200000);           
    }

    shmdt(shared);
    return 0;
}