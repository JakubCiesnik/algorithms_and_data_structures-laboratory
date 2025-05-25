// euler_check.h - header for Eulerian cycle check
#ifndef EULER_CHECK_H
#define EULER_CHECK_H

#include <stdbool.h>

#define MAX_V 1000

typedef struct {
    int matrix[MAX_V][MAX_V];
    int n; // number of vertices
} EulerGraph;

void euler_add_edge(EulerGraph* g, int u, int v);
void euler_cycle(EulerGraph* g, int v);
int is_eulerian_graph(EulerGraph* g);

#endif // EULER_CHECK_H
