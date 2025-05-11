#ifndef DAG_H
#define DAG_H

typedef struct DAG {
    int num_nodes;
    int **adj_matrix;
} DAG;

// Creation/destruction
DAG* dag_create(int num_nodes, float saturation);
void dag_free(DAG *dag);

// File I/O
int dag_save(const DAG *dag, const char *filename);
DAG* dag_load(const char *filename);

#endif
