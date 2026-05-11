#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <sys/mman.h>
#include <sys/stat.h>
// #include <semaphore.h>
// #include <sys/wait.h>

int main() {

    int processes = 0;
    printf("No.of processes(P): ");
    scanf("%d", &processes);
    int resources = 0;
    printf("No.of resources(R): ");
    scanf("%d", &resources);

    printf("Instances of each resource: \n");
    int instances[resources];
    int inst = 0;
    for (int i = 0; i < resources; i++) {
        printf("R%d: ",inst++);
        scanf("%d", &instances[i]);
    }

    int alloMat[processes][resources];

    int p = 0;
    printf("Allocation Matrix: \n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", p++);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &alloMat[i][j]);
        }
    }

    int pp = 0;
    int reqMat[processes][resources];
    printf("Request Matrix: \n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", pp++);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &reqMat[i][j]);
        }
    }


    int availMat[resources];
    for (int j = 0; j < resources; j++) {
        int sum = 0;
        for (int i = 0; i < processes; i++) {
            sum += alloMat[i][j];
        }
        availMat[j] = instances[j] - sum;
    }
    
    int ppp = 0;
    printf("Initial Available Matrix: \n");
    for (int j = 0; j < resources; j++) {
        printf("R%d: %d\n", ppp++, availMat[j]);
    }

    int finish[processes];
    for(int i = 0; i < processes; i++){
        finish[i] = 0;
    }

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int possible = 1;
                for (int j = 0; j < resources; j++) {
                    if (reqMat[i][j] > availMat[j]) {
                        possible = 0;
                        break;
                    }       
                }

                if  (possible) {
                    for (int j = 0; j < resources; j++) {
                        // availMat[j] -= reqMat[i][j];    /*Decrement the resources*/
                        availMat[j] += alloMat[i][j];      /*free the resources taken by process Pi*/
                    }
                        finish[i] = 1;
                        changed = 1;
                }
            }   
        }
    }

    int deadlock = 0;
    for (int i = 0; i < processes; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock) {
        printf("\n");
        printf("> Deadlock Detected \n");
        printf("> Processes in deadlock: ");
        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                printf(" | P%d | ", i);
            }
        }
        printf("\n\n");
    } else {
        printf("\n");
        printf("> No Deadlock Detected \n\n");
    }

}
