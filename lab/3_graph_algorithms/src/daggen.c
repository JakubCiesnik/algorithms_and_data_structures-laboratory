#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

// Reuse store_matrix from dag.c
extern void store_matrix(const char*, int**, int);

// Generate a connected DAG of n vertices, 60% edge saturation
static int** generate_connected_dag(int n) {
    int max_edges = n * (n - 1) / 2;
    int target    = (int)ceil(0.6 * max_edges);

    // 1) Allocate zeroed adjacency matrix
    int** mat = calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(int));

    // 2) Create a random topological order
    int* order = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) order[i] = i;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    // 3) Ensure connectivity with a simple chain
    for (int i = 0; i < n - 1; i++)
        mat[order[i]][order[i + 1]] = 1;
    int count = n - 1;

    // 4) Randomly add until reaching 60% of all possible edges
    while (count < target) {
        int i = rand() % n, j = rand() % n;
        if (i < j && !mat[order[i]][order[j]]) {
            mat[order[i]][order[j]] = 1;
            count++;
        }
    }

    free(order);
    return mat;
}

int main(void) {
    srand((unsigned)time(NULL));

    for (int n = 100; n <= 1500; n += 100) {
        int** mat;
        char filename[64];

        mat = generate_connected_dag(n);
        snprintf(filename, sizeof(filename), "dataset/dag_%d.txt", n);
        store_matrix(filename, mat, n);

        // Cleanup
        for (int i = 0; i < n; i++) free(mat[i]);
        free(mat);
    }
    return 0;
}

