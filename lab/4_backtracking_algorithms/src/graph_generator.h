#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "def_graph.h"

// Checks if a graph is connected using DFS
int is_connected(Graph* g);

// Generates a random, connected, Eulerian & Hamiltonian graph with given density
void generate_euler_hamilton_graph(Graph* g, int n, double density);

#endif // GRAPH_GENERATOR_H
