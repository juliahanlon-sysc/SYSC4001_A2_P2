#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) return 1;               // fork failed

    if (pid == 0) {
        // Child: replace with process2 executable
        execl("./process2", "process2", (char*)NULL);
        // If exec returns it failed
        perror("exec");
        return 1;
    }

    // Parent
    int counter = 0;
    int cycle = 0;

    while (1) {
        
        if (counter % 3 == 0) {
            printf("Process 1: Cycle %d: %d is a multiple of 3\n", cycle, counter);
        } else {
            printf("Process 1: Cycle %d\n", cycle);
        }
        counter++;
        cycle++;
        sleep(1);
    }
}
