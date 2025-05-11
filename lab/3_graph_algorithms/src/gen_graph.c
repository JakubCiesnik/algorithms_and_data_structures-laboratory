#include "dag.h"
#include <stdlib.h>
#include <time.h>

void generate_dag(int nodes, float saturation, const char *filename) {
    srand(time(NULL));
    DAG *dag = dag_create(nodes);
    
    // Random topological order
    int *order = malloc(nodes * sizeof(int));
    for (int i = 0; i < nodes; i++) order[i] = i;
    for (int i = nodes-1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }
    
    // Create edges
    int max_edges = nodes * (nodes - 1) / 2;
    int target_edges = saturation * max_edges;
    
    for (int i = 0; i < nodes; i++) {
        for (int j = i+1; j < nodes; j++) {
            if (rand() % max_edges < target_edges) {
                dag->adj_matrix[order[i]][order[j]] = 1;
                target_edges--;
            }
            max_edges--;
        }
    }
    
    char path[256];
    snprintf(path, sizeof(path), "dataset/%s.txt", filename);
    dag_save_to_file(dag, path);
    
    free(order);
    dag_free(dag);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <nodes> <saturation> <filename>\n", argv[0]);
        return 1;
    }
    
    generate_dag(atoi(argv[1]), atof(argv[2]), argv[3]);
    return 0;
}
