#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node type from dag.c
typedef struct Node {
    int        vertex;
    struct Node* next;
} Node;

// Reuse matrix_to_list from dag.c
extern Node** matrix_to_list(int**, int);

// Matrix-based Prim's algorithm (O(V^2))
int prim_mst_matrix(int** weight, int n) {
    int* in_mst = calloc(n, sizeof(int));
    int* min_e   = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) min_e[i] = INT_MAX;
    min_e[0] = 0;

    int total_weight = 0;
    for (int iter = 0; iter < n; iter++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!in_mst[i] && (u < 0 || min_e[i] < min_e[u]))
                u = i;

        in_mst[u] = 1;
        total_weight += min_e[u];

        for (int v = 0; v < n; v++)
            if (!in_mst[v] && weight[u][v] && weight[u][v] < min_e[v])
                min_e[v] = weight[u][v];
    }

    free(in_mst);
    free(min_e);
    return total_weight;
}

// List-based Prim's: adjacency-list traversal + weight matrix
int prim_mst_list(int** weight, int n) {
    Node** adj = matrix_to_list(weight, n);
    int* in_mst = calloc(n, sizeof(int));
    int* min_e   = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) min_e[i] = INT_MAX;
    min_e[0] = 0;

    int total_weight = 0;
    for (int iter = 0; iter < n; iter++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!in_mst[i] && (u < 0 || min_e[i] < min_e[u]))
                u = i;

        in_mst[u] = 1;
        total_weight += min_e[u];

        for (Node* p = adj[u]; p; p = p->next) {
            int v = p->vertex;
            if (!in_mst[v] && weight[u][v] < min_e[v])
                min_e[v] = weight[u][v];
        }
    }

    // Cleanup
    for (int i = 0; i < n; i++) {
        Node* p = adj[i];
        while (p) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(adj);
    free(in_mst);
    free(min_e);

    return total_weight;
}

