#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: reads from pipe
        close(fd[1]);   // close write end

        read(fd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);

        close(fd[0]);
    }
    else {
        // Parent process: writes to pipe
        close(fd[0]);   // close read end

        char message[] = "Hello from parent!";
        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }

    return 0;
}
