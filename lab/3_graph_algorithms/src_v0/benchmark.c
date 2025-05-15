#include "dag.h"
#include <stdio.h>
#include <time.h>

void benchmark(const char *filename) {
    clock_t start = clock();
    DAG *dag = dag_load_from_file(filename);
    double load_time = (double)(clock() - start) / CLOCKS_PER_SEC;
    
    // Add benchmark operations here
    // Example: count edges
    start = clock();
    int edge_count = 0;
    for (int i = 0; i < dag->num_nodes; i++) {
        for (int j = 0; j < dag->num_nodes; j++) {
            if (dag->adj_matrix[i][j]) edge_count++;
        }
    }
    double count_time = (double)(clock() - start) / CLOCKS_PER_SEC;
    
    char result_path[256];
    snprintf(result_path, sizeof(result_path), "benchmark/results.csv");
    
    FILE *results = fopen(result_path, "a");
    fprintf(results, "%s,%d,%.6f,%.6f\n", 
            filename, dag->num_nodes, load_time, count_time);
    fclose(results);
    
    dag_free(dag);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    benchmark(argv[1]);
    return 0;
}
