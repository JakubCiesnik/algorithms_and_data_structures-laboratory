#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h> // for long ints

// C Libraries
#include "../C_libraries/additional-functions.c"

// // Build list and tree scripts
// #include "../C_algorithms/sorted-list-builder.c"
// #include "../C_algorithms/sorted-tree-builder.c"

// Constants
#define REPEAT              1                                     // How many times to repeat the algo (for getting more accurate average time, default 10 times)
#define DATASET_MULTIPLIER  1                                     // Multiplier for easier dataset swapping

#define NUMS_AMOUNT         (4000 * DATASET_MULTIPLIER)      // Enter how many numbers there are (which dataset to use)
#define BASE_PATH           "../dataset/"                    // Enter which dataset to test


// Main
int main(){
    
    // Test using an imported dataset
    char dataset_path[100];

    // edit this for differently named datasets
    sprintf(dataset_path, "%sn%d", BASE_PATH, NUMS_AMOUNT);                  // for "s2000" type datasets
    // sprintf(dataset_path, "%s%d", BASE_PATH, DATASET_MULTIPLIER);       // for "1" type datasets

    printf("Using: %s\n",dataset_path);
    FILE *file = fopen(dataset_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int64_t nums[NUMS_AMOUNT];
    int count = 0;
    
    while (fscanf(file, "%li", &nums[count]) == 1) {
        count++;
    }
    int nums_size = count;
    fclose(file);
    
    // Preparing nums backup
    // uint64_t nums_original[NUMS_AMOUNT];
    // for (int i = 0; i < NUMS_AMOUNT; i++) {
    //     nums_original[i] = nums[i];
    // }
    
    // Testing the algorithm
    clock_t begin = clock();
    for (int i = 0; i < REPEAT; i++){
        
        // Resetting array
        // for (int j = 0; j < nums_size; j++) {
        //     nums[j] = nums_original[j];
        // }

        // Choose sorting algo to test

        // TODO

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
