#ifndef DAG_GENERATOR_H
#define DAG_GENERATOR_H

#include "graph.h"

// Generates a random DAG with a given number of nodes and edge saturation.
// Saturation is a float between 0.0 and 1.0.
// For a DAG, max edges = n(n-1)/2.
Graph* generate_random_dag(int num_nodes, float saturation);

#endif // DAG_GENERATOR_H