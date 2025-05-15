#ifndef PRIM_MST_H
#define PRIM_MST_H

#include "graph.h"

// Edge structure for representing MST result
typedef struct MSTEdge {
    int u, v, weight;
} MSTEdge;

// Calculates MST using Prim's algorithm.
// Returns an array of MSTEdge structs, and sets mst_edge_count.
// The caller is responsible for freeing the returned array.
// Returns NULL on error or if graph is not suitable.

// Using Adjacency Matrix
MSTEdge* prim_mst_matrix(Graph* graph, int* mst_edge_count);

// Using Adjacency List
MSTEdge* prim_mst_list(Graph* graph, int* mst_edge_count);

// filepath: src/prim_mst.h
MSTEdge* prim_mst_list_heap(Graph* graph, int* mst_edge_count);

#endif // PRIM_MST_H