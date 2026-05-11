#include <stdio.h>
#include <stdlib.h>

#define OUTER_SIZE 1024   // 2^10
#define INNER_SIZE 1024   // 2^10
#define OFFSET_BITS 12

// Outer Page Table (Page Directory)
int *outer_table[OUTER_SIZE];

// Function to initialize dummy page tables
void init_page_tables() {
    for (int i = 0; i < OUTER_SIZE; i++) {
        outer_table[i] = NULL; // initially empty
    }
}

// Simulated frame allocation
int get_frame_number(int dir_idx, int tbl_idx) {
    // Dummy mapping (for simulation)
    return (dir_idx + tbl_idx) % 1024;
}

// MMU Translation
void translate(unsigned int virtual_address) {
    unsigned int dir_idx, tbl_idx, offset;

    // Extract bits
    dir_idx = (virtual_address >> 22) & 0x3FF;  // top 10 bits
    tbl_idx = (virtual_address >> 12) & 0x3FF;  // next 10 bits
    offset  = virtual_address & 0xFFF;          // last 12 bits

    printf("\nVirtual Address: 0x%X\n", virtual_address);
    printf("Directory Index: %u\n", dir_idx);
    printf("Table Index    : %u\n", tbl_idx);
    printf("Offset         : %u\n", offset);

    // Allocate inner page table if not present
    if (outer_table[dir_idx] == NULL) {
        outer_table[dir_idx] = (int *)malloc(INNER_SIZE * sizeof(int));

        for (int i = 0; i < INNER_SIZE; i++)
            outer_table[dir_idx][i] = -1;
    }

    // Get frame number
    int frame;
    if (outer_table[dir_idx][tbl_idx] == -1) {
        frame = get_frame_number(dir_idx, tbl_idx);
        outer_table[dir_idx][tbl_idx] = frame;
    } else {
        frame = outer_table[dir_idx][tbl_idx];
    }

    // Physical Address calculation
    unsigned int physical_address = (frame << OFFSET_BITS) | offset;

    printf("Frame Number   : %d\n", frame);
    printf("Physical Addr  : 0x%X\n", physical_address);
}

// Main function
int main() {
    unsigned int virtual_address;

    init_page_tables();

    printf("Enter Virtual Address (hex, e.g., 0x12345678): ");
    scanf("%x", &virtual_address);

    translate(virtual_address);

    return 0;
}