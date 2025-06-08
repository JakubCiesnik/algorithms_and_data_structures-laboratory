#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "knapsack.h"

#define MAX_FILES 100

// Comparison function for qsort - sorts by problem number
int compare_strings(const void *a, const void *b) {
    const char *str_a = (const char*)a;
    const char *str_b = (const char*)b;
    
    // Extract numbers from "problem_X.csv" format
    int num_a = -1, num_b = -1;
    sscanf(str_a, "problem_%d.csv", &num_a);
    sscanf(str_b, "problem_%d.csv", &num_b);
    
    // Compare by number
    return num_a - num_b;
}

// Function to free cargo_problem memory
void free_cargo_problem(cargo_problem *problem) {
    if (problem->in_cargo) {
        free(problem->in_cargo);
    }
    
    if (problem->out_cargo) {
        free(problem->out_cargo);
    }
}

// Function to benchmark algorithms on a problem file
void benchmark_file(const char *filename, FILE *output) {
    cargo_problem problem;
    clock_t start, end;
    double greedy_time, dynamic_time;
    int greedy_value, dynamic_value;

    // Read problem
    read_file(filename, &problem);

    // Run greedy algorithm
    start = clock();
    greedy_knapsack(&problem);
    end = clock();
    greedy_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    greedy_value = problem.value;
    
    // Free greedy solution before running dynamic
    if (problem.out_cargo) {
        free(problem.out_cargo);
        problem.out_cargo = NULL;
    }

    // Run dynamic algorithm (jacob version)
    start = clock();
    dynamic(&problem);
    end = clock();
    dynamic_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    dynamic_value = problem.value;

    // Calculate relative error: (D_dyn - D_greedy) / D_dyn
    double relative_error = (dynamic_value > 0) ? 
        ((double)(dynamic_value - greedy_value) / dynamic_value) * 100 : 0;

    // Write results
    fprintf(output, "%s,%d,%d,%d,%d,%.2f,%.4f,%.4f\n", 
            filename, problem.container_count, problem.capacity, 
            greedy_value, dynamic_value, relative_error, 
            greedy_time, dynamic_time);

    // Free resources
    free_cargo_problem(&problem);
}

// Function to benchmark all problems in a directory
void benchmark_dir(const char *dirname, FILE *output) {
    DIR *dir;
    struct dirent *ent;
    char path[1024];
    char filenames[MAX_FILES][256];
    int file_count = 0;

    if ((dir = opendir(dirname)) != NULL) {
        // Collect all CSV filenames first
        while ((ent = readdir(dir)) != NULL && file_count < MAX_FILES) {
            if (strstr(ent->d_name, ".csv") != NULL) {
                strcpy(filenames[file_count], ent->d_name);
                file_count++;
            }
        }
        closedir(dir);
        
        // Sort filenames to ensure consistent order
        qsort(filenames, file_count, sizeof(filenames[0]), compare_strings);
        
        // Process files in sorted order
        for (int i = 0; i < file_count; i++) {
            snprintf(path, sizeof(path), "%s/%s", dirname, filenames[i]);
            benchmark_file(path, output);
        }
    } else {
        perror("Could not open directory");
    }
}


// Main runtime
int main() {
    // Create output file
    FILE *output = fopen("benchmark_results.csv", "w");
    if (!output) {
        perror("Error creating output file");
        return 1;
    }

    // Write CSV header
    fprintf(output, "Problem,Container Count,Capacity,Greedy Value,Dynamic Value,Relative Error(%%),Greedy Time(ms),Dynamic Time(ms)\n");

    // Benchmark both directories
    benchmark_dir("dataset/var_capacity", output);
    benchmark_dir("dataset/var_container_count", output);

    fclose(output);
    return 0;
}
