#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    // Process 2 - child
    int counter = 0;
    int cycle = 0;

    while (1) {
        if (counter % 3 == 0) {
            printf("Process 2: Cycle %d: %d is a multiple of 3\n", cycle, counter);
        } else {
            printf("Process 2: Cycle %d\n", cycle);
        }
        counter--;  
        cycle++;
        sleep(1);
    }
}
