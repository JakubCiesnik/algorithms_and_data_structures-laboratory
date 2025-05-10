#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int num_nodes;
    int **adj_matrix;
} DAG;

DAG* create_dag(int num_nodes, float saturation) {
    DAG *dag = malloc(sizeof(DAG));
    dag->num_nodes = num_nodes;
    dag->adj_matrix = calloc(num_nodes, sizeof(int*));
    
    for (int i = 0; i < num_nodes; i++) {
        dag->adj_matrix[i] = calloc(num_nodes, sizeof(int));
    }

    // Random topological order
    int *order = malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++) order[i] = i;
    for (int i = num_nodes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }

    // Add edges with given saturation
    int max_edges = num_nodes * (num_nodes - 1) / 2;
    int target_edges = saturation * max_edges;
    
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i + 1; j < num_nodes; j++) {
            if (rand() % max_edges < target_edges) {
                dag->adj_matrix[order[i]][order[j]] = 1;
                target_edges--;
            }
            max_edges--;
        }
    }

    // Print matrix to stdout
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            printf("%d ", dag->adj_matrix[i][j]);
        }
        printf("\n");
    }

    free(order);
    return dag;
}

void free_dag(DAG *dag) {
    for (int i = 0; i < dag->num_nodes; i++) {
        free(dag->adj_matrix[i]);
    }
    free(dag->adj_matrix);
    free(dag);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int nodes = argc > 1 ? atoi(argv[1]) : 5;
    float saturation = argc > 2 ? atof(argv[2]) : 0.6f;
    
    DAG *dag = create_dag(nodes, saturation);
    free_dag(dag);
    return 0;
}
