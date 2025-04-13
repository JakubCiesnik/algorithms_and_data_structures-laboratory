void generate_random_array(int *array, int amount, int min, int max){
    for (int i = 0; i < amount; i++){
        array[i] = rand() % (max - min + 1) + min;
    }
}

// swapping integers using XOR for optimized time and minimal memory consumption
void swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int return_smallest_arg(int *nums, int start, int end){
    int smallest_arg = start;
    for (int i = start+1; i < end; i++)
    {
        if (nums[i] < nums[smallest_arg]){
            smallest_arg = i;
        }
    }
    return smallest_arg;
}

// Prints the array
void print_array(int nums[], int size){
    printf("Nums: {");
    for (int i = 0; i < size;i++){
        printf("%i, ", nums[i]);
    }
    printf("}\n");
}