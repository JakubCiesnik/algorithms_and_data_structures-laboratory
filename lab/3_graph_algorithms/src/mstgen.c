#include "mst.h"
#include <stdio.h>
#include <stdlib.h>

#define START_N 1000
#define STEP_N 1000
#define POINTS 15
#define OUTPUT_DIR "dataset"

int main() {
    const double densities[] = {0.3, 0.7};

    for (int i = 0; i < POINTS; i++) {
        int n = START_N + i * STEP_N;
        for (int d = 0; d < 2; d++) {
            double dens = densities[d];
            int **mat = generate_mst_graph(n, dens);
            char filename[256];
            snprintf(filename, sizeof(filename), OUTPUT_DIR"/mst_%d_%.0f.txt", n, dens * 100);
            save_matrix(filename, mat, n);
            free_matrix(mat, n);
            printf("Generated MST graph with %d nodes, %.0f%% density: %s\n", n, dens * 100, filename);
        }
    }
    return 0;
}

