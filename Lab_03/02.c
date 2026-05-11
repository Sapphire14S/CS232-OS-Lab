#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
    pid_t pid = getpid();
    printf("\nTime expired! Killing process %d\n", pid);
    printf("Process: %d", pid);
    printf(" killed by SIGKILL\n");
    kill(pid, SIGKILL);

    // kill(pid, SIGTERM);
}

int main() {
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);
    printf("Press Ctrl+C within 5 seconds to exit...\n");

    signal(SIGALRM, alarm_handler);
    // signal(SIGTERM, alarm_handler);
    alarm(5);

    while (1) {
        pause();   // Wait for signals
    }

    return 0;
}
