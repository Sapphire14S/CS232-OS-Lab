#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main() {
    int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
    int nFrames, nPages;
    int pages[MAX_PAGES];
    
    int clock = 0;
    int pageFaults = 0;

    // Input
    printf("Enter no.of frames: ");
    scanf("%d", &nFrames);

    printf("Enter no.of pages: ");
    scanf("%d", &nPages);

    printf("Enter reference string:\n");
    for(int i = 0; i < nPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames
    for(int i = 0; i < nFrames; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    // Processing
    for(int i = 0; i < nPages; i++) {
        int page = pages[i];
        int hit = 0;

        clock++;  // increment logical clock

        // Check HIT
        for(int j = 0; j < nFrames; j++) {
            if(frames[j] == page) {
                hit = 1;
                lastUsed[j] = clock;
                break;
            }
        }

        // If MISS
        if(!hit) {
            pageFaults++;

            int emptyIndex = -1;

            // Check for empty frame
            for(int j = 0; j < nFrames; j++) {
                if(frames[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if(emptyIndex != -1) {
                // Load into empty frame
                frames[emptyIndex] = page;
                lastUsed[emptyIndex] = clock;
            } else {
                // Find LRU (smallest lastUsed)
                int lruIndex = 0;
                for(int j = 1; j < nFrames; j++) {
                    if(lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j;
                    }
                }

                // Replace
                frames[lruIndex] = page;
                lastUsed[lruIndex] = clock;
            }
        }

        // printing frames
        printf("After page %d: ", page);
        for(int j = 0; j < nFrames; j++) {
            if(frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if(hit)
            printf("(HIT)\n");
        else
            printf("(FAULT)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}