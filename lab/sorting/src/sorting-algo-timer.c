#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// C Libraries
#include "../C_libraries/additional-functions.c"

// Sorting algos
#include "../C_algorithms/bubble-sort.c"
#include "../C_algorithms/insertion-sort.c"
#include "../C_algorithms/selection-sort.c"
#include "../C_algorithms/heap-sort.c"
#include "../C_algorithms/merge-sort.c"
#include "../C_algorithms/quick-sort.c"

// Constants
#define REPEAT              100                                  // How many times to repeat the algo (for getting more accurate average time, default 10 times)
#define DATASET_MULTIPLIER  14                                // Multiplier for easier dataset swapping

#define NUMS_AMOUNT         (2000 + 4000 * DATASET_MULTIPLIER)  // Enter how many numbers there are (which dataset to use)
#define BASE_PATH           "../dataset/random/s"               // Enter which dataset to test

#define NUMS_MIN_VAL        1                                   // only for randomly generated test
#define NUMS_MAX_VAL        10000                               // only for randomly generated test

// Main
int main(){
    
    // Test using randomly generate nums
    // srand(clock());         // Random gen seed - using clock() instead of time(NULL) for more optimal random nums
    // int nums[NUMS_AMOUNT];
    // generate_random_array(nums, NUMS_AMOUNT, NUMS_MIN_VAL, NUMS_MAX_VAL);
    // int nums_size = sizeof(nums) / sizeof(nums[0]);

    // Test using an imported dataset
    char dataset_path[100];
    sprintf(dataset_path, "%s%d", BASE_PATH, NUMS_AMOUNT);
    printf("Using: %s\n",dataset_path);
    FILE *file = fopen(dataset_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int nums[NUMS_AMOUNT];
    int count = 0;
    
    while (fscanf(file, "%d", &nums[count]) == 1) {
        count++;
    }
    int nums_size = count;
    fclose(file);
    
    // Preparing nums backup
    int nums_original[NUMS_AMOUNT];
    for (int i = 0; i < NUMS_AMOUNT; i++) {
        nums_original[i] = nums[i];
    }
    
    // Testing the algorithm
    clock_t begin = clock();
    for (int i = 0; i < REPEAT; i++){
        // Resetting array
        for (int j = 0; j < nums_size; j++) {
            nums[j] = nums_original[j];
        }

        // Choose sorting algo to test

        // bubble_sort(nums, nums_size);
        // insertion_sort(nums, nums_size);
        // selection_sort(nums, nums_size);
        // heap_sort(nums, nums_size);
        // merge_sort(nums, nums_size);
        quick_sort(nums, nums_size);      
    }
    clock_t duration = (clock() - begin);

    printf("Time taken in seconds: %f\n", ((double)duration / CLOCKS_PER_SEC)/ REPEAT);
    
    // Check if the first 100 numbers are sorted
    int is_sorted = 1; // Assume sorted until proven otherwise
    for (int i = 0; i < 99; i++) { // Compare each element with the next
        if (nums[i] > nums[i + 1]) {
            is_sorted = 0;
            break;
        }
    }

    if (is_sorted) {
        printf("The first 100 numbers are sorted correctly.\n");
    } else {
        printf("The first 100 numbers are NOT sorted correctly.\n");
    }

    // Print the first 100 numbers for verification
    for (int i = 0; i < 100; i++) {
        printf("%i ", nums[i]);
    }
    printf("\n");
    
    return 0;
}