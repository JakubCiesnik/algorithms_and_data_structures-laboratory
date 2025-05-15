#ifndef UNDIRECTED_GRAPH_GENERATOR_H
#define UNDIRECTED_GRAPH_GENERATOR_H

#include "graph.h"

// Generates a random connected undirected weighted graph.
// Saturation is a float between 0.0 and 1.0.
// Max edges for undirected graph = n(n-1)/2.
// Weights are random integers between min_weight and max_weight.
Graph* generate_random_undirected_graph(int num_nodes, float saturation, int min_weight, int max_weight);

#endif // UNDIRECTED_GRAPH_GENERATOR_H