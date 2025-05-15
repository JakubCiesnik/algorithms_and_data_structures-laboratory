#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

// Reuse store_matrix from dag.c
extern void store_matrix(const char*, int**, int);

// Generate a connected undirected weighted graph at given density
static int** generate_mst_graph(int n, double density) {
    int max_edges = n * (n - 1) / 2;
    int target    = (int)ceil(density * max_edges);

    int** w = calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        w[i] = calloc(n, sizeof(int));
    }

    // Ensure connectivity: simple chain
    for (int i = 0; i < n - 1; i++) {
        int wt = rand() % 1000 + 1;
        w[i][i + 1] = w[i + 1][i] = wt;
    }
    int count = n - 1;

    // Add random edges until reaching desired density
    while (count < target) {
        int u = rand() % n, v = rand() % n;
        if (u != v && !w[u][v]) {
            int wt = rand() % 1000 + 1;
            w[u][v] = w[v][u] = wt;
            count++;
        }
    }

    return w;
}

int main(void) {
    srand((unsigned)time(NULL));

    for (int n = 100; n <= 1000; n += 50) {
        for (int d = 30; d <= 70; d += 40) {
            double density = d / 100.0;
            int** w = generate_mst_graph(n, density);

            char filename[64];
            snprintf(filename, sizeof(filename), "dataset/mst_%d_%d.txt", d, n);
            store_matrix(filename, w, n);

            for (int i = 0; i < n; i++) free(w[i]);
            free(w);
        }
    }
    return 0;
}

