#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;

    while ((ch = getchar()) != EOF) {
        // Convert uppercase to lowercase
        if (isupper(ch)) {
            ch = tolower(ch);
        }
        // Convert lowercase to uppercase
        else if (islower(ch)) {
            ch = toupper(ch);
        }

        // Write character to stdout
        putchar(ch);
    }

    exit(0);
}