#include <stdlib.h> // For rand()
#include <stdio.h>  // For printf(), etc.
#include <stdint.h> // For int64_t

// Swap function
// void swap(unsigned int *a, unsigned int *b){
//     unsigned int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// Function Declarations
void quick_sort_right(int64_t *nums, int length);
void quicksort_r(int64_t *nums, int p, int r);
int partition_r(int64_t *nums, int p, int r);

// Function Definitions

// This function starts quicksort_r with a right-pivot strategy.
void quick_sort_right(int64_t *nums, int length){
    quicksort_r(nums, 0, length - 1);
}

void quicksort_r(int64_t *nums, int p, int r){
    if (p < r){
        int q = partition_r(nums, p, r);
        quicksort_r(nums, p, q);
        quicksort_r(nums, q + 1, r);
    }
}

int partition_r(int64_t *nums, int p, int r){
    // Use the rightmost element as pivot, then swap it with first element.
    // This ensures that the standard Hoare partition_r algorithm works correctly.
    swap(&nums[p], &nums[r]);
    int64_t x = nums[p];  // Pivot value is now at nums[p].
    int i = p - 1;
    int j = r + 1;
    
    while (1){
        // Move j leftwards until we find an element not greater than pivot.
        do {
            j--;
        } while (nums[j] > x);
        
        // Move i rightwards until we find an element not less than pivot.
        do {
            i++;
        } while (nums[i] < x);
        
        if (i < j){
            swap(&nums[i], &nums[j]);
        }
        else{
            return j; // Return the partition_r index.
        }
    }
}
