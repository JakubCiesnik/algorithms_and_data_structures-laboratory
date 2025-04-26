#include <stdint.h> // For int64_t

// Functions Declarations
void quick_sort_middle(int64_t *nums, int length);
void quicksort_m(int64_t *nums, int p, int r);
int partition_m(int64_t *nums, int p, int r);
// void swap(int64_t *a, int64_t *b);

// Functions Definitions
void quick_sort_middle(int64_t *nums, int length){
    quicksort_m(nums, 0, length - 1);
    // Done
}

void quicksort_m(int64_t *nums, int p, int r){
    if (p < r){
        int q = partition_m(nums, p, r);
        quicksort_m(nums, p, q);
        quicksort_m(nums, q + 1, r);
    }
}

int partition_m(int64_t *nums, int p, int r){
    int64_t x = nums[(p + r) / 2];
    int i = p - 1;
    int j = r + 1;
    while (1){
        do{
            j--;
        }
        while(nums[j] > x);
        
        do{
            i++;
        }
        while(nums[i] < x);

        if (i < j){
            swap(&nums[i], &nums[j]);
        }
        else{
            return j;
        }
    }    
}

// void swap(int64_t *a, int64_t *b){
//     int64_t temp = *a;
//     *a = *b;
//     *b = temp;
// }