#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int first = 1;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            if (!first) {
                printf(" ");
            }

            printf("%s", argv[i]);
            first = 0;
        }
    }

    // Print newline only if something was printed
    if (!first) {
        printf("\n");
    }

    return 0;
}