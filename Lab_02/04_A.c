#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // First child
    pid1 = fork();
    if (pid1 == 0) {
        // Child 1
        for (int i = 1; i <= 5; i++) {
            printf("Child 1: %d\n", i);
            sleep(1);
        }
        return 0;
    }

    // Second child
    pid2 = fork();
    if (pid2 == 0) {
        // Child 2
        for (int i = 6; i <= 10; i++) {
            printf("Child 2: %d\n", i);
            sleep(1);
        }
        return 0;
    }

    // Parent process waits for both children
    wait(NULL);
    wait(NULL);

    printf("Parent: Both children have finished execution\n");

    return 0;
}
