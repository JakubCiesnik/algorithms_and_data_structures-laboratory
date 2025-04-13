// Pseudocode uses starting index as 1 meanwhile C uses 0, so all code was corrected to accomodate that

// Functions Declarations
void quick_sort(int *nums, int length);
void quicksort(int *nums, int p, int r);
int partition(int *nums, int p, int r);

// Functions Definitions
void quick_sort(int *nums, int length){
    quicksort(nums, 0, length - 1);
    // Done
}

void quicksort(int *nums, int p, int r){
    if (p < r){
        int q = partition(nums, p, r);
        quicksort(nums, p, q);
        quicksort(nums, q + 1, r);
    }
}

int partition(int *nums, int p, int r){
    int x = nums[(p + r) / 2];
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