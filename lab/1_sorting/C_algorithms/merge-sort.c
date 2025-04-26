// Pseudocode uses starting index as 1 meanwhile C uses 0, so all code was corrected to accomodate that

// Functions Declarations
void merge_sort(int *nums, int length);
void merge_sort_inner(int *nums, int l, int r, int *nums2);

// Functions Definitions
void merge_sort(int *nums, int length){
    // making a copy of array
    int nums2[length];
    for (int i = 0; i < length; i++){
        nums2[i] = nums[i];
    }
    merge_sort_inner(nums, 0, length - 1, nums2);
    // Done
}

void merge_sort_inner(int *nums, int l, int r, int *nums2){
    int m = (l + r)/2;
    if ((m - l) > 0){
        merge_sort_inner(nums, l, m, nums2);
    }
    if ((r - m) > 1){
        merge_sort_inner(nums, m + 1, r, nums2);
    }
    int i = l;
    int j = m + 1;
    for (int k = l; k <= r; k++){
        if (((i <= m) && (j > r)) || (((i <= m) && (j <= r)) && (nums[i] <= nums[j]))){
            nums2[k] = nums[i];
            i++;
        }
        else{
            nums2[k] = nums[j];
            j++;
        }
    } 
    for (int k = l; k <= r; k++){
        nums[k] = nums2[k];
    }
}