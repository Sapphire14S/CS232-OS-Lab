#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process (PID: %d)\n", getpid());
        printf("Executing external program using execlp...\n");

        // Replace child process with 'ls -l'
        execlp("ls", "ls", "-l", NULL);

        // Executes only if exec fails
        perror("execlp failed");
    }
    else {
        // Parent process
        wait(NULL);   
        printf("Parent Process (PID: %d)\n", getpid());
        printf("Child process finished execution\n");
    }

    return 0;
}
