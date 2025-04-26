// swapping integers using XOR for optimized time and minimal memory consumption
void swap(int64_t *a, int64_t *b){
    if(a == b) return; // Do nothing if the adresses==values are the same.
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
// ALTERNATIVE SWAP FUNCTION - noticed quicksort didnt like the XOR one
// void swap(int64_t *a, int64_t *b){
//     int64_t temp = *a;
//     *a = *b;
//     *b = temp;
// }

// Generates random int from <min, max> range (including both nums)
int64_t random_int(int64_t min, int64_t max){
    return rand() % (max - min + 1) + min;
}