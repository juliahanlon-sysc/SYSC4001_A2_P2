#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) return 1;   // fork failed

    if (pid == 0) {
        int counter = 0;
        while (1) {
            printf("Process 2 (pid=%d): counter = %d\n", getpid(), counter++);
            sleep(1);
        }
    } else {
        int counter = 0;
        while (1) {
            printf("Process 1 (pid=%d): counter = %d\n", getpid(), counter++);
            sleep(1);
        }
    }
}