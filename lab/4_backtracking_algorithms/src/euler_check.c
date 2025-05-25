// euler_check.c - implementation for Eulerian cycle check
#include "euler_check.h"
#include <stdio.h>

int is_eulerian_graph(EulerGraph* g) {
    for (int i = 0; i < g->n; i++) {
        int degree = 0;
        for (int j = 0; j < g->n; j++) {
            degree += g->matrix[i][j];
        }
        if (degree % 2 != 0) {
            return 0;
        }
    }
    return 1;
}

void euler_add_edge(EulerGraph* g, int u, int v) {
    g->matrix[u][v]++;
    g->matrix[v][u]++;
}

// modified 25.05.2025, commented out lines are for debugging purposes

void euler_cycle(EulerGraph* g, int v) {
    for (int w = 0; w < g->n; w++) {
        while (g->matrix[v][w] > 0) {
            g->matrix[v][w]--;
            g->matrix[w][v]--;
            euler_cycle(g, w);
        }
    }
    // printf("%d ", v);
}