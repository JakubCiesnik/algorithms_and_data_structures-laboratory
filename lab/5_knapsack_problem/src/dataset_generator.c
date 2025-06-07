#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
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
        
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            continue;
        }
        
        fprintf(file, "%d,%d\n", container_count, capacity);
        for (int j = 0; j < container_count; j++) {
            int value = rand() % 31 + 1;
            int weight = rand() % 31 + 1;
            fprintf(file, "%d,%d\n", value, weight);
        }
        fclose(file);
    }

    // Set 2: Container count constant (100), capacity iterated (10 to 150 in steps of 10)
    for (int i = 0; i < 15; i++) {
        int container_count = 100;
        int capacity = 10 + i * 10;
        char filename[100];
        sprintf(filename, SET2DIR "problem_%d.csv", i);
        
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            continue;
        }
        
        fprintf(file, "%d,%d\n", container_count, capacity);
        for (int j = 0; j < container_count; j++) {
            int value = rand() % 31 + 1;
            int weight = rand() % 31 + 1;
            fprintf(file, "%d,%d\n", value, weight);
        }
        fclose(file);
    }

    return 0;
}
