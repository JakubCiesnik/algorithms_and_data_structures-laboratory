#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <stdint.h>

// Adjacency‐list node
typedef struct AdjNode {
    int v;
    int weight;          // for weighted graphs; 0 if unweighted
    struct AdjNode *next;
} AdjNode;

// Matrix I/O and allocation
int **alloc_matrix(int n);
void free_matrix(int **mat, int n);
int **load_matrix(const char *fname, int *n_out);
void save_matrix(const char *fname, int **mat, int n);

// Convert between representations
AdjNode **matrix_to_list(int **mat, int n, int weighted);
void free_adjlist(AdjNode **list, int n);

#endif // GRAPH_UTILS_H
