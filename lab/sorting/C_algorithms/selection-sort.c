void selection_sort(int *nums, int size){
    // sorting
    for (int i = 0; i < size; i++)
    {
        int j = return_smallest_arg(nums, i, size);
        if (nums[i] != nums[j]){
            swap(&nums[i],&nums[j]);
        }
    }
}