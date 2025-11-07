#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int *shared = (int *)shmat(shmid, NULL, 0);

    shared[0] = 3;   // multiple value
    shared[1] = 0;   // counter value

    int started = 0;

    while (1) {
        int c = shared[1];

        if (c % shared[0] == 0)
            printf("Process 1: Cycle %d – %d is a multiple of %d\n", c, c, shared[0]);
        else
            printf("Process 1: Cycle %d\n", c);

        if (c > 500) break;

        shared[1] = c + 1;

        if (!started && shared[1] > 100) {
            started = 1;
            if (fork() == 0) {
                execl("./process2_101194310_101299427", "process2_101194310_101299427", (char *)NULL);
                _exit(127);
            }
        }

        sleep(1);
    }

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}