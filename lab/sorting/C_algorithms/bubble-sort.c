void bubble_sort(int *nums, int size){
    // sorting
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size-1; j++){
            if (nums[j] > nums[j+1]){
               swap(&nums[j], &nums[j+1]);
            }
        }
    }
}