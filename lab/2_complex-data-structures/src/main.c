#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../C_algorithms/sorted_linked_list.c"
#include "../C_algorithms/binary_search_tree.c"

#define FILE_NAME "../dataset/n4000"
#define NUMBERS_COUNT 4000

int main() {
    struct list_node *list = NULL;
    struct bst_node *bst = NULL;
    uint32_t numbers[NUMBERS_COUNT];
    FILE *file;
    clock_t start, end;
    double insertion_time_list, search_time_list;
    double insertion_time_bst, search_time_bst;
    int i = 0;

    // Open the file
    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Read numbers
    while (i < NUMBERS_COUNT && fscanf(file, "%u", &numbers[i]) == 1) {
        i++;
    }
    fclose(file);

    if (i != NUMBERS_COUNT) {
        fprintf(stderr, "Error: Expected %d numbers, but read %d.\n", NUMBERS_COUNT, i);
        return EXIT_FAILURE;
    }

    printf("Successfully loaded %d numbers from '%s'.\n\n", i, FILE_NAME);

    set_debug(0); // No printing

    // === Linked List Benchmark ===
    printf("Benchmarking Linked List...\n");

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        insert_sorted(&list, numbers[j]);
    }
    end = clock();
    insertion_time_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        int pos = find_position(list, numbers[j]);
        if (pos == -1) {
            fprintf(stderr, "List Error: Value %u not found!\n", numbers[j]);
        }
    }
    end = clock();
    search_time_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("List Insertion Time: %f seconds\n", insertion_time_list);
    printf("List Search Time: %f seconds\n\n", search_time_list);

    free_list(list);

    // === Binary Search Tree Benchmark ===
    printf("Benchmarking Binary Search Tree...\n");

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        bst = bst_insert(bst, numbers[j]);
    }
    end = clock();
    insertion_time_bst = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        if (!bst_find(bst, numbers[j])) {
            fprintf(stderr, "BST Error: Value %u not found!\n", numbers[j]);
        }
    }
    end = clock();
    search_time_bst = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("BST Insertion Time: %f seconds\n", insertion_time_bst);
    printf("BST Search Time: %f seconds\n", search_time_bst);

    bst_free(bst);

    return 0;
}
