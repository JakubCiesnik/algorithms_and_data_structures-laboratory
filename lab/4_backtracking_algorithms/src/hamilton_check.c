// hamilton_check.c - implementation for hamilton cycle check
#include "hamilton_check.h"
#include <stdio.h>
#include <string.h>

void hamilton_add_edge(HamiltonGraph* g, int u, int v) {
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;
}

static bool is_safe(HamiltonGraph* g, int v, int path[], int pos, bool visited[]) {
    if (g->matrix[path[pos - 1]][v] == 0) return false;
    if (visited[v]) return false;
    return true;
}

bool hamilton_cycle_util(HamiltonGraph* g, int pos, int path[], bool visited[]) {
    if (pos == g->n) {
        return g->matrix[path[pos - 1]][path[0]] == 1;
    }
    for (int v = 1; v < g->n; v++) {
        if (is_safe(g, v, path, pos, visited)) {
            path[pos] = v;
            visited[v] = true;
            if (hamilton_cycle_util(g, pos + 1, path, visited)) return true;
            visited[v] = false;
        }
    }
    return false;
}

// modified 25.05.2025, commented out lines are for debugging purposes

bool hamilton_cycle(HamiltonGraph* g) {
    int path[MAX_V];
    bool visited[MAX_V];
    memset(path, -1, sizeof(path));
    memset(visited, 0, sizeof(visited));
    path[0] = 0;
    visited[0] = true;
    if (hamilton_cycle_util(g, 1, path, visited)) {
        // printf("Hamiltonian cycle exists: ");
        // for (int i = 0; i < g->n; i++) printf("%d ", path[i]);
        // printf("%d\n", path[0]);
        return true;
    } else {
        // printf("No Hamiltonian cycle exists\n");
        return false;
    }
}