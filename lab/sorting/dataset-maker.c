#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "C_libraries/additional-functions.c"

// Functions
void generate_dataset(const char *filename, int n, int min, int max) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    // Allocating memory for array 
    int *random_array = malloc(n * sizeof(int));
    
    generate_random_array(random_array, n, min, max);
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", random_array[i]);
    }

    free(random_array);
    fclose(file);
}

// Main
int main(){

    // ENTER DETAILS TO GENERATE DATASETS
    int base_amount =           2000;
    int min_value =             10;
    int max_value =             10000;
    int offset =                4000;   // enter the offset of every dataset example: if base = 1000 and offset = 500, first dataset will have 1000 and second will have 1500 etc 
    int amount_of_datasets =    15;
    
    char folder[] = "datasets/random";  // Choose where will the datasets be generated in
    char fname[] = "s";                 //name of the file with format "{fname}{base_amount}" for example "s2000"


    // GENERATING DATASETS (truncated from the largest one - as agreed upon)

    char name[100];
    
    for (int i = 0; i < amount_of_datasets; i++){
        int current_amount = base_amount + i * offset;
        sprintf(name, "%s/%s%d", folder, fname, current_amount);
        printf("Generating dataset: %s\n", name);
        generate_dataset(name, current_amount, min_value, max_value);
    }
        
    return 0;
}