#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "knapsack.h"

// Function to implement dynamic programming knapsack
void dynamic(cargo_problem *problem) {
    int n = problem->container_count;
    int W = problem->capacity;

    // Create DP table
    int **dp = malloc((n+1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = malloc((W+1) * sizeof(int));
    }

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (problem->in_cargo[i-1][1] <= w) {
                int include = problem->in_cargo[i-1][0] + dp[i-1][w - problem->in_cargo[i-1][1]];
                int exclude = dp[i-1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    // Store result
    problem->value = dp[n][W];

    // Cleanup
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

// Function to free cargo_problem memory
void free_cargo_problem(cargo_problem *problem) {
    if (problem->in_cargo) {
        for (int i = 0; i < problem->container_count; i++) {
            free(problem->in_cargo[i]);
        }
        free(problem->in_cargo);
    }
    
    if (problem->out_cargo) {
        for (int i = 0; i < problem->out_count; i++) {
            free(problem->out_cargo[i]);
        }
        free(problem->out_cargo);
    }
}

// Function to benchmark algorithms on a problem file
void benchmark_file(const char *filename, FILE *output) {
    cargo_problem problem;
    clock_t start, end;
    double greedy_time, dynamic_time;
    int greedy_value, dynamic_value;
    double accuracy;

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
        for (int i = 0; i < problem.out_count; i++) {
            free(problem.out_cargo[i]);
        }
        free(problem.out_cargo);
        problem.out_cargo = NULL;
    }

    // Run dynamic algorithm
    start = clock();
    dynamic(&problem);
    end = clock();
    dynamic_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    dynamic_value = problem.value;

    // Calculate accuracy
    accuracy = (dynamic_value > 0) ? 
        ((double)greedy_value / dynamic_value) * 100 : 0;

    // Write results
    fprintf(output, "%s,%d,%d,%.2f,%.4f,%.4f\n", 
            filename, greedy_value, dynamic_value, accuracy, 
            greedy_time, dynamic_time);

    // Free resources
    free_cargo_problem(&problem);
}

// Function to benchmark all problems in a directory
void benchmark_dir(const char *dirname, FILE *output) {
    DIR *dir;
    struct dirent *ent;
    char path[1024];

    if ((dir = opendir(dirname)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {  // Regular file
                snprintf(path, sizeof(path), "%s/%s", dirname, ent->d_name);
                benchmark_file(path, output);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

int main() {
    // Create output file
    FILE *output = fopen("benchmark_results.csv", "w");
    if (!output) {
        perror("Error creating output file");
        return 1;
    }

    // Write CSV header
    fprintf(output, "Problem,Greedy Value,Dynamic Value,Accuracy(%%),Greedy Time(ms),Dynamic Time(ms)\n");

    // Benchmark both directories
    benchmark_dir("dataset/var_capacity", output);
    benchmark_dir("dataset/var_container_count", output);

    fclose(output);
    return 0;
}
