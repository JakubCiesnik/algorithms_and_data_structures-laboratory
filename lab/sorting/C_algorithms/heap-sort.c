// Pseudocode uses starting index as 1 meanwhile C uses 0, so all code was corrected to accomodate that

// Functions Declarations
void heap_sort(int *nums, int heapsize);
void build_heap(int *nums, int heapsize);
void heapify(int *nums, int i, int heapsize);

// Functions Definitions
void heap_sort(int *nums, int heapsize){
    build_heap(nums, heapsize);
    for (int i = heapsize - 1; i >= 1; i--){
        swap(&nums[0], &nums[i]);
        heapsize--;
        heapify(nums, 0, heapsize);
    }
}

void build_heap(int *nums, int heapsize){
    for (int i = heapsize/2 - 1; i >=0; i--){
        heapify(nums, i, heapsize);
    }
}

void heapify(int *nums, int i, int heapsize){
    int l = i*2 + 1;
    int r = i*2 + 2;
    int largest;
    if (l < heapsize && nums[l] > nums[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r < heapsize &&  nums[r] > nums[largest]){
        largest = r;
    }
    if (largest != i){
        swap(&nums[i], &nums[largest]);
        heapify(nums, largest, heapsize);
    }
}