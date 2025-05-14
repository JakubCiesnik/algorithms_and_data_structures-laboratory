#ifndef DAG_H
#define DAG_H

#include "graph_utils.h"

// Generate a connected DAG of n nodes at given density [0,1]
int **generate_dag(int n, double density);

// Topological sort:  
//   - matrix version writes into out_order[0..n-1]  
//   - list version likewise
void topo_sort_matrix(int **mat, int n, int *out_order);
void topo_sort_list(AdjNode **adj, int n, int *out_order);

#endif // DAG_H
