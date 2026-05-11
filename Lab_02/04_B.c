#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        for (int i = 1; i <= 5; i++) {
            printf("Child 1: %d\n", i);
            sleep(1);
        }
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        for (int i = 6; i <= 10; i++) {
            printf("Child 2: %d\n", i);
            sleep(1);
        }
        return 0;
    }

    // Parent waits for specific children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Parent: Both children completed (waitpid)\n");

    return 0;
}
