#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, newfd;

    // Open file output.txt
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Close standard output
    close(STDOUT_FILENO);

    // Duplicate file descriptor
    newfd = dup(fd);

    // Now stdout points to output.txt
    printf("This will be written to the file.\n");

    // Close file descriptor
    close(fd);

    return 0;
}
