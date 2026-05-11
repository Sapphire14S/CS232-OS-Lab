#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd_in, fd_out;
    char buffer[100];

    // Open input file
    fd_in = open("input.txt", O_RDONLY);
    if (fd_in < 0) {
        perror("open input.txt failed");
        return 1;
    }

    // Open output file
    fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("open output.txt failed");
        return 1;
    }

    // Redirect stdin to input.txt
    dup2(fd_in, STDIN_FILENO);

    // Redirect stdout to output.txt
    dup2(fd_out, STDOUT_FILENO);

    // Close original file descriptors
    close(fd_in);
    close(fd_out);

    // Read from stdin (now input.txt)
    fgets(buffer, sizeof(buffer), stdin);

    // Write to stdout (now output.txt)
    printf("Data read from input file:\n");
    printf("%s", buffer);

    return 0;
}
