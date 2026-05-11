#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 100

typedef struct {
    int page_ID;
    int reference_bit;
} Frame;

Frame frame[MAX_FRAMES];
int hand = 0;   


void start_frame() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frame[i].page_ID = -1;  // !Empty
        frame[i].reference_bit = 0;
    }
}

int find_page(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frame[i].page_ID == page) {
            return i;  // !Found
        }
    }
    return -1;  // !Not found
}


int find_victim() {
    while (1) {
        if (frame[hand].reference_bit == 0) {
            int victim = hand;
            hand = (hand+1) % MAX_FRAMES;
            return victim;
        } else {
            frame[hand].reference_bit = 0;
            hand = (hand+1) % MAX_FRAMES;
        }
    }
}


void print_frames() {
    printf("Frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frame[i].page_ID == -1)
            printf("[ - ] ");
        else
            printf("[%d|%d] ", frame[i].page_ID, frame[i].reference_bit);
    }
    printf("\n");
}


int main() {
    int pages[MAX_PAGES], n;

    printf("\n------------------------------- INPUT SECTION ----------------------------------------\n");
    printf("Enter no.of page requests: ");
    scanf("%d", &n);

    printf("Enter page sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    start_frame();

    int page_faults = 0;

    printf("\n------------------------------- Output Section ---------------------------------------\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int index = find_page(page);

        printf("Accessing %d: ", page);

        if (index != -1) {
            // !HIT
            frame[index].reference_bit = 1;
            printf("HIT\n");
        } else {
            // !FAULT
            int victim = find_victim();
            frame[victim].page_ID = page;
            frame[victim].reference_bit = 1;

            page_faults++;
            printf("FAULT (Replaced frame %d)\n", victim);
        }

        print_frames();
    }

    printf("\nTotal Page Faults = %d\n", page_faults);

    return 0;
}
