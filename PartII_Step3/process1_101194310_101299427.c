#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void p1print(int cycle, int value) {
    if (value % 3 == 0)
        printf("Process 1: Cycle %d: %d is a multiple of 3\n", cycle, value);
    else
        printf("Process 1: Cycle %d\n", cycle);
}

int main(void) {
    int counter = 0;
    int cycle = 0;
    p1print(cycle, counter);
    counter++; 
    cycle++;
    sleep(1);

    pid_t pid = fork();
    if (pid < 0) return 1;

    if (pid == 0) {
        execl("./process2_101194310_101299427", "process2_101194310_101299427", (char*)NULL);
        perror("exec");
        _exit(127);
    }

    printf("Process 1: started Process 2 (pid=%d)\n", (int)pid);
    printf("Process 1: waiting...\n");
    int status = 0;
    waitpid(pid, &status, 0);
    printf("Process 1: done. Exiting.\n");
    return 0;
}
