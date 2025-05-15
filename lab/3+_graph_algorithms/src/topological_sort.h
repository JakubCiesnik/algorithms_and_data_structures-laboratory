#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "graph.h"

// Performs topological sort on a DAG.
// Stores the sorted node indices in sorted_order_result array (must be pre-allocated).
// Returns true if successful (graph is a DAG), false otherwise (cycle detected or error).

// Using Adjacency Matrix
bool topological_sort_matrix(Graph* graph, int* sorted_order_result);

// Using Adjacency List
bool topological_sort_list(Graph* graph, int* sorted_order_result);

#endif // TOPOLOGICAL_SORT_H