#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/wait.h>

int main() {

        pid_t pid;

        pid = fork();

        if (pid < 0) {
                printf("Process Failed\n");
        } else if (pid == 0) {
                printf("Child Process \n");
                printf("Child PID: %d" , getpid());
                printf("\n");
                printf("Parent PID: %d", getppid());
                printf("\n");
        } else {
                wait(NULL);
                printf("Parent Process\n");
                printf("Parent PID: %d", getpid());
                printf("\n");
        }

        return 0;
}
