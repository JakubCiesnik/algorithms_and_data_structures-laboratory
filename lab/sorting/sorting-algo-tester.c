#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "C_libraries\additional-functions.c"

// Function prototypes for the sorting algorithm to be tested
#include "C_algorithms\bubble-sort.c"
#include "C_algorithms\insertion-sort.c"
#include "C_algorithms\selection-sort.c"

// Helper function to check if an array is sorted
bool is_sorted(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Test function
void test_sorting_algorithm() {
    int test_cases[][10] = {
        {5, 2, 9, 1, 5, 6, 0, 3, 8, 7}, // Random order
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, // Already sorted
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // Reverse order
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // All elements the same
        {3, 3, 2, 2, 1, 1, 0, 0, -1, -1} // Mixed with duplicates
    };

    int sizes[] = {10, 10, 10, 10, 10};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_tests; i++) {
        int *arr = malloc(sizes[i] * sizeof(int));
        memcpy(arr, test_cases[i], sizes[i] * sizeof(int));

        // Sorting algos (uncomment to test a given algorithm)

        
        // bubble_sort(arr, sizes[i]);
        // insertion_sort(arr, sizes[i]);
        selection_sort(arr, sizes[i]);


        if (is_sorted(arr, sizes[i])) {
            printf("Test case %d passed.\n", i + 1);
        } else {
            printf("Test case %d failed.\n", i + 1);
        }
        print_array(arr,sizes[i]);

        free(arr);
    }
}

int main() {
    test_sorting_algorithm();
    return 0;
}