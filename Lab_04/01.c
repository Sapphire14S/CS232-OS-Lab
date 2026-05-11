#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int isCompleted;
};

int main() {
    int n, time = 0, completed = 0;
    float totalWaiting = 0, totalTurnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].pid = i + 1;
        p[i].isCompleted = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minBurst = 9999;

        // Find shortest job among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].isCompleted == 0) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("P%d (%d-%d) | ",
                   p[idx].pid,
                   time,
                   time + p[idx].burst);

            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            totalWaiting += p[idx].waiting;
            totalTurnaround += p[idx].turnaround;

            p[idx].isCompleted = 1;
            completed++;
        } else {
            time++;  // If no process has arrived
        }
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
