#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

#define BUF_SIZE 100

jmp_buf env;

void alarm_handler(int sig) {
    longjmp(env, 1);   // Jump back to setjmp with timeout status
}

int main() {
    char buffer[BUF_SIZE];

    write(1, "Enter your name (10 seconds): ", 30);

    if (setjmp(env) != 0) {
        write(1, "\nTimeout!\n", 10);
        exit(1);
    }

    // signal(SIGALRM, alarm_handler);
    signal(SIGTERM, alarm_handler);
    alarm(10);

    int n = read(0, buffer, BUF_SIZE - 1);

    alarm(0);

    if (n > 0) {
        buffer[n] = '\0';
        write(1, "\nHello, ", 8);
        write(1, buffer, n);
    }

    return 0;
}
