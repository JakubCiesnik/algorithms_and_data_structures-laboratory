
#include "graph_utils.h"
#include <stdlib.h>
#include <stdio.h>

// ---------- Matrix alloc/free ----------
int **alloc_matrix(int n) {
    int **m = malloc(n * sizeof(*m));
    for (int i = 0; i < n; i++)
        m[i] = calloc(n, sizeof(*m[i]));
    return m;
}

void free_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

// ---------- I/O: first line is 'n' ----------
int **load_matrix(const char *fname, int *n_out) {
    FILE *f = fopen(fname, "r");
    if (!f) { perror(fname); exit(1); }
    int n;
    if (fscanf(f, "%d\n", &n) != 1) {
        fprintf(stderr, "Bad format in %s\n", fname);
        exit(1);
    }
    *n_out = n;
    int **m = alloc_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(f, "%d", &m[i][j]) != 1) {
                fprintf(stderr, "Bad data in %s at %d,%d\n", fname, i, j);
                exit(1);
            }
        }
    }
    fclose(f);
    return m;
}

void save_matrix(const char *fname, int **mat, int n) {
    FILE *f = fopen(fname, "w");
    if (!f) { perror(fname); exit(1); }
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

// ---------- Convert to adjacency list ----------
// If weighted==0, use mat[u][v] as boolean; else use mat[u][v] as weight.
AdjNode **matrix_to_list(int **mat, int n, int weighted) {
    AdjNode **adj = calloc(n, sizeof(*adj));
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            int w = mat[u][v];
            if (w) {
                AdjNode *node = malloc(sizeof(*node));
                node->v = v;
                node->weight = weighted ? w : 0;
                node->next = adj[u];
                adj[u] = node;
            }
        }
    }
    return adj;
}

void free_adjlist(AdjNode **list, int n) {
    for (int i = 0; i < n; i++) {
        AdjNode *p = list[i];
        while (p) {
            AdjNode *nx = p->next;
            free(p);
            p = nx;
        }
    }
    free(list);
}
