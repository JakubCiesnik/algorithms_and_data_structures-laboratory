// hamilton_check.h - header for Hamiltonian cycle check
#ifndef HAMILTON_CHECK_H
#define HAMILTON_CHECK_H

#include <stdbool.h>

#define MAX_V 800

typedef struct {
    int matrix[MAX_V][MAX_V];
    int n; // number of vertices
} HamiltonGraph;

bool hamilton_cycle_util(HamiltonGraph* g, int pos, int path[], bool visited[]);
bool hamilton_cycle(HamiltonGraph* g);
void hamilton_add_edge(HamiltonGraph* g, int u, int v);

#endif // HAMILTON_CHECK_H
