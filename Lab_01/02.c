#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;
    int count = 0;

    while ((ch = getchar()) != EOF) {
        // Count non-alphabetic characters
        if (!isalpha(ch)) {
            count++;
        }

        // Write character to stdout
        putchar(ch);
    }

    // Print final count to stderr
    fprintf(stderr, "\nNon-alphabetic count: %d\n", count);

    exit(0);
}