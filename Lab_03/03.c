#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void C(int x) {
    printf("Inside function C\n");

    if (x == 0) {
        printf("Error! Divison by 0.\n");
        longjmp(env, 1);
    }

    printf("Result: %d\n", 10 / x);
}

void B(int x) {
    printf("Inside func B\n");
    C(x);
}

void A(int x) {
    printf("Inside func A\n");
    B(x);
}

int main() {

    // int value = 0;   // Change this to non-zero to avoid error
    int value = 0;

    if (setjmp(env) == 0) {
        printf("Inside main: Calling A\n");
        A(value);
        printf("Back in main normally (no error)\n");
    } else {
        printf("Back in main using longjmp after error\n");
    }

    printf("Program continues safely...\n");
    return 0;

}
