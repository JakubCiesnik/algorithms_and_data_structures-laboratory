#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../C_libraries/additional-functions.c"

// Generate an unsorted array of non duplicated natural numbers
int main(){

    // Set amount of nums generated and the range of them starting from 1
    int amount =        100;                     
    int start_index =   0;
    int end_index =     start_index + amount - 1;
    
    // Set amount of swapping cycles to unsort the array, for more random array set higher value
    int swap_cycles =   amount + 10;

    // Choose where will the datasets be generated in
    char folder[] = "../dataset";
    
    // Prefix of filename with format "{fprefix}{amount}" for example "s2000"
    char fprefix[] = "n";


    // Main runtime
    srand(time(NULL));

    // Generate simple array from start to end
    int64_t array[amount];
    for (int i = 0; i < amount; i++)
    {
        array[i] = i+1;
    }

    // Unsort the array
    for (int i = 0; i < swap_cycles; i++)
    {
        swap(&array[random_int(start_index, end_index)], &array[random_int(start_index, end_index)]);
    }

    // Print array (debug)
    // printf("array = {");
    // for (int i = 0; i < amount; i++)
    // {
    //     printf("%li,",array[i]);
    // }
    // printf("};\n");
    
    // Save array to file
    char filename[100];
    sprintf(filename, "%s/%s%d", folder, fprefix, amount);
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < amount; i++) {
        fprintf(file, "%li\n", array[i]);
    }

    fclose(file);
}