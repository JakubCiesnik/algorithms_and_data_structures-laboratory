#include "graph_generator.h"
#include <stdlib.h>

// Helper to check if a graph is connected using DFS
int is_connected(Graph* g) {
    int n = g->num_nodes;
    int* visited = calloc(n, sizeof(int));
    int stack[n], top = 0;
    stack[top++] = 0;
    visited[0] = 1;
    int count = 1;
    while (top) {
        int v = stack[--top];
        for (int u = 0; u < n; u++) {
            if (g->adj_matrix[v][u] && !visited[u]) {
                visited[u] = 1;
                stack[top++] = u;
                count++;
            }
        }
    }
    int result = (count == n);
    free(visited);
    return result;
}

// Generate a simple cycle graph (Eulerian and Hamiltonian)
static void generate_cycle_graph(Graph* g, int n) {
    for (int i = 0; i < n; i++) {
        add_edge(g, i, (i+1)%n, 0);
    }
}

// Generate a random Eulerian & Hamiltonian graph with given density
void generate_euler_hamilton_graph(Graph* g, int n, double density) {
    int max_edges = n * (n-1) / 2;
    int target_edges = (int)(density * max_edges);
    generate_cycle_graph(g, n);
    int edges = n; // cycle has n edges
    // Add random edges in pairs to keep degrees even
    while (edges + 2 <= target_edges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && !g->adj_matrix[u][v]) {
            add_edge(g, u, v, 0);
            int u2 = rand() % n, v2 = rand() % n;
            while (u2 == v2 || g->adj_matrix[u2][v2]) {
                u2 = rand() % n;
                v2 = rand() % n;
            }
            add_edge(g, u2, v2, 0);
            edges += 2;
        }
    }
    // Ensure the graph is connected (should be, but check)
    if (!is_connected(g)) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g->adj_matrix[i][j] = 0;
        generate_euler_hamilton_graph(g, n, density);
    }
}
