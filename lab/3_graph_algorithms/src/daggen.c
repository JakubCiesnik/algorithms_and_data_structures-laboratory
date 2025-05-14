#include "dag.h"
#include <stdio.h>
#include <stdlib.h>

#define START_N 1000
#define STEP_N 1000
#define POINTS 15
#define OUTPUT_DIR "dataset"

int main() {
    for (int i = 0; i < POINTS; i++) {
        int n = START_N + i * STEP_N;
        int **mat = generate_dag(n, 0.6); // 60% saturation
        char filename[256];
        snprintf(filename, sizeof(filename), OUTPUT_DIR"/dag_%d.txt", n);
        save_matrix(filename, mat, n);
        free_matrix(mat, n);
        printf("Generated DAG with %d nodes: %s\n", n, filename);
    }
    return 0;
}
