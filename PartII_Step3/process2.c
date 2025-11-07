#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static void p2print(int cycle, int value) {
    if (value % 3 == 0)
        printf("Process 2: Cycle %d: %d is a multiple of 3\n", cycle, value);
    else
        printf("Process 2: Cycle %d\n", cycle);
}

int main(void) {
    int counter = 0;
    int cycle = 0;

    while (1) {
        p2print(cycle, counter);
        counter--;
        cycle++;
        if (counter < -500) {
            printf("Process 2: reached %d (< -500). Exiting.\n", counter);
            break;
        }
        sleep(1);
    }
    return 0;
}
