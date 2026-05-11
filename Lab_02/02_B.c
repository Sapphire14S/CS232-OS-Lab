#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        perror("execvp failed");
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent: Child execution completed\n");
    }

    return 0;
}
