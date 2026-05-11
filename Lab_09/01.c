#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sort(int arr[], int n) {
    for (int i = 0; i < (n-1); i++) {
        for (int j = 0; j < (n-i-1); j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// !1. SSTF 
void SSTF(int head, int requests[], int n) {
    int visited[n];
    int sequence[n];
    int total_movement = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int current = head;

    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX;
        int index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(current - requests[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        sequence[i] = requests[index];
        total_movement += min_dist;
        current = requests[index];
    }

    printf("\n\n1. SSTF \n");
    printf("   Sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", sequence[i]);

    printf("\n   Total Head Movement: %d\n", total_movement);
}

// !2. SCAN 
void SCAN(int head, int requests[], int n, int disk_size, char direction[]) {
    int left[n], right[n];
    int l = 0, r = 0;
    int sequence[100];  
    int idx = 0;
    int total_movement = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    int current = head;

    if (direction[0] == 'r' && direction[1] == 'i' && direction[2] == 'g' && direction[3] == 'h' && direction[4] == 't') {
        // Move right
        for (int i = 0; i < r; i++) {
            sequence[idx++] = right[i];
            total_movement += abs(current - right[i]);
            current = right[i];
        }

        // Go to end
        total_movement += abs(current - (disk_size - 1));
        current = disk_size - 1;

        // Reverse (left)
        for (int i = (l-1); i >= 0; i--) {
            sequence[idx++] = left[i];
            total_movement += abs(current - left[i]);
            current = left[i];
        }
    } else if (direction[0] == 'l' && direction[1] == 'e' && direction[2] == 'f' && direction[3] == 't') {
        // Move left
        for (int i = (l-1); i >= 0; i--) {
            sequence[idx++] = left[i];
            total_movement += abs(current - left[i]);
            current = left[i];
        }

        // Go to start
        total_movement += abs(current - 0);
        current = 0;

        // Reverse (right)
        for (int i = 0; i < r; i++) {
            sequence[idx++] = right[i];
            total_movement += abs(current - right[i]);
            current = right[i];
        }
    } else {
        printf("\nInvalid direction for SCAN.");
    }

    printf("\n\n2. SCAN \n");
    printf("   Sequence: ");
    for (int i = 0; i < idx; i++)
        printf("%d ", sequence[i]);

    printf("\n   Total Head Movement: %d\n", total_movement);
}

int main() {
    int n, head, disk_size;

    printf("Enter no.of requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    char direction[10];
    printf("Enter direction (left/right): ");
    scanf("%s", direction);

    SSTF(head, requests, n);
    SCAN(head, requests, n, disk_size, direction);

    return 0;
}