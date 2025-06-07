#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "knapsack.h"  // Include the header for cargo_problem and write_file

#define SET1DIR "dataset/var_container_count/"
#define SET2DIR "dataset/var_capacity/"
#define SEED 1

int main() {
    srand(SEED);

    // Create directories if they don't exist
    mkdir(SET1DIR, 0777);
    mkdir(SET2DIR, 0777);

    // Set 1: Capacity constant (100), container count iterated (10 to 150 in steps of 10)
    for (int i = 0; i < 15; i++) {
        int container_count = 10 + i * 10;
        int capacity = 100;
        char filename[100];
        sprintf(filename, SET1DIR "problem_%d.csv", i);
        
        // Initialize cargo_problem struct
        struct cargo_problem problem;
        problem.container_count = container_count;
        problem.capacity = capacity;
        
        // Allocate memory for input cargo
        problem.in_cargo = malloc(container_count * sizeof(int *));
        for (int j = 0; j < container_count; j++) {
            problem.in_cargo[j] = malloc(2 * sizeof(int));
            problem.in_cargo[j][0] = rand() % 31 + 1;  // value (1-31)
            problem.in_cargo[j][1] = rand() % 31 + 1;  // weight (1-31)
        }
        
        // Initialize unused solution fields
        problem.out_cargo = NULL;
        problem.out_count = 0;
        problem.value = 0;
        
        // Use write_file function to save problem
        write_file(filename, &problem);
        
        // Free allocated memory
        for (int j = 0; j < container_count; j++) {
            free(problem.in_cargo[j]);
        }
        free(problem.in_cargo);
    }

    // Set 2: Container count constant (100), capacity iterated (10 to 150 in steps of 10)
    for (int i = 0; i < 15; i++) {
        int container_count = 100;
        int capacity = 10 + i * 10;
        char filename[100];
        sprintf(filename, SET2DIR "problem_%d.csv", i);
        
        // Initialize cargo_problem struct
        struct cargo_problem problem;
        problem.container_count = container_count;
        problem.capacity = capacity;
        
        // Allocate memory for input cargo
        problem.in_cargo = malloc(container_count * sizeof(int *));
        for (int j = 0; j < container_count; j++) {
            problem.in_cargo[j] = malloc(2 * sizeof(int));
            problem.in_cargo[j][0] = rand() % 31 + 1;  // value (1-31)
            problem.in_cargo[j][1] = rand() % 31 + 1;  // weight (1-31)
        }
        
        // Initialize unused solution fields
        problem.out_cargo = NULL;
        problem.out_count = 0;
        problem.value = 0;
        
        // Use write_file function to save problem
        write_file(filename, &problem);
        
        // Free allocated memory
        for (int j = 0; j < container_count; j++) {
            free(problem.in_cargo[j]);
        }
        free(problem.in_cargo);
    }

    return 0;
}
