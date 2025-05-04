#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../C_algorithms/sorted_linked_list.c"
#include "../C_algorithms/binary_search_tree.c"
#include "../C_algorithms/AVL_tree.c"

#define FILE_NAME "../dataset/n60000"
#define NUMBERS_COUNT 60000

int main() {
    struct list_node *list = NULL;
    struct bst_node *bst = NULL;
    uint32_t numbers[NUMBERS_COUNT];
    FILE *file;
    clock_t start, end;
    double insertion_time_list, search_time_list, deletion_time_list;
    double insertion_time_bst, search_time_bst, deletion_time_bst;
    double insertion_time_avl, search_time_avl, deletion_time_avl;
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
    // printf("Benchmarking Linked List...\n");

    // start = clock();
    // for (int j = 0; j < NUMBERS_COUNT; j++) {
    //     insert_sorted(&list, numbers[j]);
    // }
    // end = clock();
    // insertion_time_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    // start = clock();
    // for (int j = 0; j < NUMBERS_COUNT; j++) {
    //     int pos = find_position(list, numbers[j]);
    //     if (pos == -1) {
    //         fprintf(stderr, "List Error: Value %u not found!\n", numbers[j]);
    //     }
    // }
    // end = clock();
    // search_time_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    // start = clock();
    // free_list(list);
    // end = clock();
    // deletion_time_list = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("List Insertion Time: %f seconds\n", insertion_time_list);
    // printf("List Search Time: %f seconds\n\n", search_time_list);
    // printf("List Deletion Time: %f seconds\n\n", deletion_time_list);
    printf("%f\n", insertion_time_list);
    printf("%f\n", search_time_list);
    printf("%f\n", deletion_time_list);


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

    printf("BST In-Order before balancing:\n");
    // bst_inorder_print(bst);
    printf("\n");

    int height_before = bst_get_height(bst);
    printf("Height before balancing: %d\n", height_before);

    // Balance the BST
    bst = bst_balance(bst);

    printf("\nBST In-Order after balancing:\n");
    // bst_inorder_print(bst);
    printf("\n");

    int height_after = bst_get_height(bst);
    printf("Height after balancing: %d\n", height_after);

    start = clock();
    bst_free(bst);
    end = clock();
    deletion_time_bst = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("BST Insertion Time: %f seconds\n", insertion_time_bst);
    // printf("BST Search Time: %f seconds\n", search_time_bst);
    // printf("BST Deletion Time: %f seconds\n", deletion_time_bst);
    printf("%f\n", insertion_time_bst);
    printf("%f\n", search_time_bst);
    printf("%f\n", deletion_time_bst);
    
    struct avl_node *avl = NULL;

    // === AVL Tree Benchmark ===
    printf("Benchmarking AVL Tree...\n");

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        avl = avl_insert(avl, numbers[j]);
    }
    end = clock();
    insertion_time_avl = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int j = 0; j < NUMBERS_COUNT; j++) {
        if (!avl_find(avl, numbers[j])) {
            fprintf(stderr, "AVL Error: Value %u not found!\n", numbers[j]);
        }
    }
    end = clock();
    search_time_avl = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    
    start = clock();
    avl_free(avl);
    end = clock();
    deletion_time_avl = ((double)(end - start)) / CLOCKS_PER_SEC;

    // printf("AVL Insertion Time: %f seconds\n", insertion_time_avl);
    // printf("AVL Search Time: %f seconds\n", search_time_avl);
    // printf("AVL Deletion Time: %f seconds\n", deletion_time_avl);
    printf("%f\n", insertion_time_avl);
    printf("%f\n", search_time_avl);
    printf("%f\n", deletion_time_avl);
    


    return 0;
}

