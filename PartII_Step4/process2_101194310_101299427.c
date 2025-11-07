#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int) * 2, 0666);
    int *shared = (int *)shmat(shmid, NULL, 0);

    int multiple = shared[0];

    while (1) {
        int c = shared[1];
        if (c > 500) break;

        if (c % multiple == 0)
            printf("Process 2: Cycle %d – %d is a multiple of %d\n", c, c, multiple);
        else
            printf("Process 2: Cycle %d\n", c);

        sleep(1);
    }

    shmdt(shared);
    return 0;
}