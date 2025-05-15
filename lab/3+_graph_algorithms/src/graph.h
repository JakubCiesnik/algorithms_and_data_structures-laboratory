#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>

// Node for adjacency list
typedef struct AdjListNode {
    int dest;
    int weight; // For weighted graphs
    struct AdjListNode* next;
} AdjListNode;

// Graph structure
typedef struct Graph {
    int num_nodes;
    bool is_directed;
    bool is_weighted;

    // Adjacency Matrix representation
    // For unweighted, 0 or 1. For weighted, stores weight, 0 if no edge.
    // Using -1 or a large value for no edge in weighted graphs might be better if 0 is a valid weight.
    // For simplicity here, 0 means no edge or 0 weight if allowed.
    int** adj_matrix;

    // Adjacency List representation
    AdjListNode** adj_list_array; // Array of adjacency lists (AdjListNode* heads)

} Graph;

// Graph creation and manipulation
Graph* create_graph(int num_nodes, bool is_directed, bool is_weighted);
void add_edge(Graph* graph, int src, int dest, int weight); // Universal add edge
void free_graph(Graph* graph);
void print_graph_matrix(const Graph* graph);
void print_graph_list(const Graph* graph);

#endif // GRAPH_H