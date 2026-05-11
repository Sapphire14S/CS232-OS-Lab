#include <stdio.h>

#define NB 5   // number of blocks
#define NP 4   // number of processes

// Function to print results
void printResult(int allocation[], int blocks[], int processes[]) {
    int total_frag = 0;

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < NP; i++) {
        printf("P%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Calculate fragmentation
    for (int i = 0; i < NB; i++)
        total_frag += blocks[i];

    printf("Total Fragmentation = %d KB\n", total_frag);
    printf("\n***************************************************\n");
}

// FIRST FIT
void firstFit(int blocks[], int processes[]) {
    int allocation[NP];
    int b[NB];

    // Copy blocks
    for (int i = 0; i < NB; i++) b[i] = blocks[i];

    for (int i = 0; i < NP; i++) allocation[i] = -1;

    for (int i = 0; i < NP; i++) {
        for (int j = 0; j < NB; j++) {
            if (b[j] >= processes[i]) {
                allocation[i] = j;
                b[j] -= processes[i];
                break;
            }
        }
    }

    printf("\n> First Fit \n");
    printResult(allocation, b, processes);
}

// BEST FIT
void bestFit(int blocks[], int processes[]) {
    int allocation[NP];
    int b[NB];

    for (int i = 0; i < NB; i++) b[i] = blocks[i];
    for (int i = 0; i < NP; i++) allocation[i] = -1;

    for (int i = 0; i < NP; i++) {
        int bestIdx = -1;

        for (int j = 0; j < NB; j++) {
            if (b[j] >= processes[i]) {
                if (bestIdx == -1 || b[j] < b[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            b[bestIdx] -= processes[i];
        }
    }

    printf("\n> Best Fit \n");
    printResult(allocation, b, processes);
}

// WORST FIT
void worstFit(int blocks[], int processes[]) {
    int allocation[NP];
    int b[NB];

    for (int i = 0; i < NB; i++) b[i] = blocks[i];
    for (int i = 0; i < NP; i++) allocation[i] = -1;

    for (int i = 0; i < NP; i++) {
        int worstIdx = -1;

        for (int j = 0; j < NB; j++) {
            if (b[j] >= processes[i]) {
                if (worstIdx == -1 || b[j] > b[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            b[worstIdx] -= processes[i];
        }
    }

    printf("\n> Worst Fit \n");
    printResult(allocation, b, processes);
}

// Main function
int main() {
    int blocks[NB] = {100, 500, 200, 300, 600};
    int processes[NP] = {212, 417, 112, 426};

    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);

    return 0;
}