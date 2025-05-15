#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "dag_generator.h"
#include "topological_sort.h"

// ...existing includes and definitions...

#define NUM_POINTS 15
#define START_N 1000
#define STEP_N 1000
#define SATURATION 0.6f
#define NUM_RUNS 3 // You can increase for more stable averages

int main() {
    srand(time(NULL));
    FILE* results_file = fopen("results/toposort_benchmark.csv", "w");
    if (!results_file) {
        perror("Failed to open results file");
        return 1;
    }
    fprintf(results_file, "NumNodes,TimeMatrix_ms,TimeList_ms\n");

    printf("Running Topological Sort Benchmark (Saturation: %.2f)...\n", SATURATION);
    printf("%-10s | %-15s | %-15s\n", "Nodes", "Matrix (ms)", "List (ms)");
    printf("-----------|-----------------|-----------------\n");

    for (int i = 0; i < NUM_POINTS; i++) {
        int n = START_N + i * STEP_N;

        double total_time_matrix = 0;
        double total_time_list = 0;
        bool success_matrix_run = true;
        bool success_list_run = true;

        for (int run = 0; run < NUM_RUNS; ++run) {
            Graph* dag = generate_random_dag(n, SATURATION);
            if (!dag) {
                fprintf(stderr, "Failed to generate DAG for n=%d\n", n);
                success_matrix_run = false; success_list_run = false;
                break;
            }

            int* sorted_order_matrix = (int*)malloc(n * sizeof(int));
            int* sorted_order_list = (int*)malloc(n * sizeof(int));
            if(!sorted_order_matrix || !sorted_order_list){
                fprintf(stderr, "Malloc failed for sorted_order arrays\n");
                free(sorted_order_matrix); free(sorted_order_list); free_graph(dag);
                success_matrix_run = false; success_list_run = false;
                break;
            }

            // Benchmark Matrix
            clock_t start_matrix = clock();
            bool ts_matrix_ok = topological_sort_matrix(dag, sorted_order_matrix);
            clock_t end_matrix = clock();
            if(ts_matrix_ok) total_time_matrix += ((double)(end_matrix - start_matrix) / CLOCKS_PER_SEC) * 1000.0;
            else success_matrix_run = false;

            // Benchmark List
            clock_t start_list = clock();
            bool ts_list_ok = topological_sort_list(dag, sorted_order_list);
            clock_t end_list = clock();
            if(ts_list_ok) total_time_list += ((double)(end_list - start_list) / CLOCKS_PER_SEC) * 1000.0;
            else success_list_run = false;

            free(sorted_order_matrix);
            free(sorted_order_list);
            free_graph(dag);
            if (!success_matrix_run && !success_list_run) break;
        }

        double avg_time_matrix = success_matrix_run ? total_time_matrix / NUM_RUNS : -1.0;
        double avg_time_list = success_list_run ? total_time_list / NUM_RUNS : -1.0;

        printf("%-10d | %-15.4f | %-15.4f\n", n, avg_time_matrix, avg_time_list);
        fprintf(results_file, "%d,%.4f,%.4f\n", n, avg_time_matrix, avg_time_list);
    }

    fclose(results_file);
    printf("Benchmark finished. Results saved to results/toposort_benchmark.csv\n");
    return 0;
}