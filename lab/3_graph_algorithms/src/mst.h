#ifndef MST_H
#define MST_H

#include "graph_utils.h"
#include <stdint.h>

// Generate a connected, weighted undirected graph
int **generate_mst_graph(int n, double density);

// Prim's MST
//   - prim_matrix returns total weight using O(n^2) matrix method
//   - prim_list returns total weight using O(E log V) list+heap
int64_t prim_matrix(int **mat, int n);
int64_t prim_list(int **mat, int n);

#endif // MST_H
