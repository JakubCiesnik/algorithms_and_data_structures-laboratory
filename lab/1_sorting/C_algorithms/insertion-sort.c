void insertion_sort(int *nums, int size){
    // sorting
    for (int i = 1; i < size; i++){
        int key = nums[i]; 
        int j = i - 1;
        while (j >= 0 && nums[j] > key){
            nums[j+1] = nums[j];
            j = j-1;
        }
        nums[j+1] = key;
    }
}