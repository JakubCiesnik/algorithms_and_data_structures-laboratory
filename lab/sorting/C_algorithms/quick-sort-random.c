#include <stdlib.h> // For rand(), srand()
#include <stdio.h>  // For printf()
#include <time.h>   // For time()
#include <stdint.h> // For int64_t

// Function Declarations
void quick_sort_random(int64_t *nums, int length);
void quicksort_random(int64_t *nums, int p, int r);
int partition_random(int64_t *nums, int p, int r);
// void swap(int64_t *a, int64_t *b);

// Function Definitions

// Initializes random seed and calls quicksort on the whole array.
void quick_sort_random(int64_t *nums, int length){
    srand(time(NULL));  // Initialize random seed.
    quicksort_random(nums, 0, length - 1);
}

void quicksort_random(int64_t *nums, int p, int r){
    if (p < r){
        int q = partition_random(nums, p, r);
        quicksort_random(nums, p, q);
        quicksort_random(nums, q + 1, r);
    }
}

// Hoare partition using a random pivot.
int partition_random(int64_t *nums, int p, int r){
    // Choose a random pivot in the range [p, r].
    int pivot_index = p + rand() % (r - p + 1);
    // Swap the chosen pivot with the first element so that the pivot is at nums[p].
    swap(&nums[p], &nums[pivot_index]);
    int64_t x = nums[p];  // Pivot value.
    int i = p - 1;
    int j = r + 1;
    while (1){
        // Move j left until an element <= x is found.
        do {
            j--;
        } while (nums[j] > x);
        // Move i right until an element >= x is found.
        do {
            i++;
        } while (nums[i] < x);
        if (i < j){
            swap(&nums[i], &nums[j]);
        } else {
            return j;
        }
    }
}

// Swap function for two int64_t values.
// void swap(int64_t *a, int64_t *b){
//     int64_t temp = *a;
//     *a = *b;
//     *b = temp;
// }

// Simple test in main.
// int main(){
//     int64_t arr[] = {702680348, 3702488201, 3702049935, 3702034860};
//     int length = sizeof(arr) / sizeof(arr[0]);
    
//     quick_sort_random(arr, length);
    
//     for (int i = 0; i < length; i++){
//         printf("%ld ", arr[i]);
//     }
//     printf("\n");
    
//     return 0;
// }
