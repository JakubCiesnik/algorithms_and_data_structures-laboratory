#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h> // for unsigned ints

// C Libraries
#include "../C_libraries/additional-functions.c"

// Sorting algos
// #include "../C_algorithms/bubble-sort.c"
// #include "../C_algorithms/insertion-sort.c"
// #include "../C_algorithms/selection-sort.c"
// #include "../C_algorithms/heap-sort.c"
// #include "../C_algorithms/merge-sort.c"
#include "../C_algorithms/quick-sort-middle.c"
#include "../C_algorithms/quick-sort-right.c"
#include "../C_algorithms/quick-sort-random.c"

// Constants
#define REPEAT              1000                                     // How many times to repeat the algo (for getting more accurate average time, default 10 times)
#define DATASET_MULTIPLIER  6                                     // Multiplier for easier dataset swapping

#define NUMS_AMOUNT         (4000 * DATASET_MULTIPLIER)      // Enter how many numbers there are (which dataset to use)
#define BASE_PATH           "../dataset/A_shaped/"                    // Enter which dataset to test

#define NUMS_MIN_VAL        1                                       // only for randomly generated test
#define NUMS_MAX_VAL        10000                                   // only for randomly generated test

// Main
int main(){
    
    // Test using randomly generate nums
    // srand(clock());         // Random gen seed - using clock() instead of time(NULL) for more optimal random nums
    // uint64_t nums[NUMS_AMOUNT];
    // generate_random_array(nums, NUMS_AMOUNT, NUMS_MIN_VAL, NUMS_MAX_VAL);
    // int nums_size = sizeof(nums) / sizeof(nums[0]);

    // Test using an imported dataset
    char dataset_path[100];

    // edit this for differently named datasets
    // sprintf(dataset_path, "%s%d", BASE_PATH, NUMS_AMOUNT);                  // for "s2000" type datasets
    sprintf(dataset_path, "%s%d", BASE_PATH, DATASET_MULTIPLIER);       // for "1" type datasets

    printf("Using: %s\n",dataset_path);
    FILE *file = fopen(dataset_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    uint64_t nums[NUMS_AMOUNT];
    int count = 0;
    
    while (fscanf(file, "%lu", &nums[count]) == 1) { // switched to unsigned 64-bit ints
        count++;
    }
    int nums_size = count;
    fclose(file);
    
    // Preparing nums backup
    uint64_t nums_original[NUMS_AMOUNT];
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
        // insertion_sort(nums, nums_size);     // 1
        // selection_sort(nums, nums_size);     // 2
        // heap_sort(nums, nums_size);          // 3
        // merge_sort(nums, nums_size);         // 4
        // quick_sort(nums, nums_size); 
        quick_sort_middle(nums, nums_size);
        // quick_sort_right(nums, nums_size);
        // quick_sort_random(nums, nums_size);
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
        printf("%lu ", nums[i]);
    }
    printf("\n");

    return 0;
}
