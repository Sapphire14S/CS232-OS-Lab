#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, tq;
    float totalWaiting = 0, totalTurnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].remaining = p[i].burst;
    }
    
    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    printf("\nGantt Chart:\n");
    printf("| ");
    
    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {

            if (p[i].arrival <= time && p[i].remaining > 0) {

                executed = 1;

                printf("P%d (%d-", p[i].pid, time);

                if (p[i].remaining > tq) {
                    time += tq;
                    p[i].remaining -= tq;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].completion = time;
                    completed++;
                }

                printf("%d) | ", time);
            }
        }

        if (!executed) {
            time++;  // If no process has arrived
        }
    }

    // Calculate WT and TAT
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTurnaround / n);

    return 0;
}
