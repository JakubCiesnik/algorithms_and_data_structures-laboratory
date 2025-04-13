#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// C Libraries
#include "../C_libraries/additional-functions.c"

// Sorting algos
#include "../C_algorithms/bubble-sort.c"
#include "../C_algorithms/insertion-sort.c"
#include "../C_algorithms/selection-sort.c"

// Constants
#define REPEAT          12                       // How many times to repeat the algo (for getting more accurate average time)
#define DATASET         "../dataset/random/s2000" // Enter which dataset to test
#define NUMS_AMOUNT     2000                    // Enter how many numbers there are

#define NUMS_MIN_VAL    1                       // only for randomly generated test
#define NUMS_MAX_VAL    10000                   // only for randomly generated test

// Main
int main(){
    
    // Test using randomly generate nums
    // srand(clock());         // Random gen seed - using clock() instead of time(NULL) for more optimal random nums
    // int nums[NUMS_AMOUNT];
    // generate_random_array(nums, NUMS_AMOUNT, NUMS_MIN_VAL, NUMS_MAX_VAL);
    // int nums_size = sizeof(nums) / sizeof(nums[0]);

    // Test using an imported dataset
    char dataset[] = DATASET;
    FILE *file = fopen(dataset, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int nums[NUMS_AMOUNT];
    int count = 0;

    while (fscanf(file, "%d", &nums[count]) == 1) {
        count++;
    }
    fclose(file);
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    
    // Testing the algorithm

    clock_t begin = clock();
    for (int i = 0; i < REPEAT; i++){
        // Choose sorting algo to test
        bubble_sort(nums, nums_size);
        // insertion_sort(nums, nums_size);
        // selection_sort(nums, nums_size);
    }
    clock_t duration = (clock() - begin) / REPEAT;


    printf("Time taken in seconds: %f\n", (double)duration / CLOCKS_PER_SEC);

    // print_array(nums, nums_size);

    return 0;
}