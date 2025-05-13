#include "dag.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Private helper functions
static void shuffle_nodes(int *array, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

static void connect_nodes(DAG *dag, int *order) {
    // Create spanning tree
    for (int i = 1; i < dag->num_nodes; i++) {
        int parent = rand() % i;
        dag->adj_matrix[order[parent]][order[i]] = 1;
    }
}

DAG* dag_create(int num_nodes, float saturation) {
    // Validate input
    if (num_nodes < 1) return NULL;
    float min_sat = (num_nodes-1.0f)/(num_nodes*(num_nodes-1)/2);
    if (saturation < min_sat) {
        fprintf(stderr, "Saturation must be at least %.4f for connectivity\n", min_sat);
        return NULL;
    }

    // Allocate DAG structure
    DAG *dag = malloc(sizeof(DAG));
    dag->num_nodes = num_nodes;
    dag->adj_matrix = malloc(num_nodes * sizeof(int*));
    
    // Initialize adjacency matrix
    for (int i = 0; i < num_nodes; i++) {
        dag->adj_matrix[i] = calloc(num_nodes, sizeof(int));
    }

    // Create random node order
    int *order = malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++) order[i] = i;
    shuffle_nodes(order, num_nodes);

    // Phase 1: Ensure connectivity
    connect_nodes(dag, order);

    // Phase 2: Add remaining edges
    const int total_possible = num_nodes*(num_nodes-1)/2;
    const int target_edges = saturation * total_possible;
    int current_edges = num_nodes - 1;
    
    // Calculate probability for remaining edges
    float p = (target_edges - current_edges) / 
             (float)(total_possible - (num_nodes-1));

    // Add edges probabilistically
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i+1; j < num_nodes; j++) {
            if (!dag->adj_matrix[order[i]][order[j]] && 
               ((float)rand()/RAND_MAX) <= p) {
                dag->adj_matrix[order[i]][order[j]] = 1;
                current_edges++;
            }
        }
    }

    // Cleanup
    free(order);
    return dag;
}

// Rest of file I/O functions...

void dag_free(DAG *dag) {
    for (int i = 0; i < dag->num_nodes; i++) {
        free(dag->adj_matrix[i]);
    }
    free(dag->adj_matrix);
    free(dag);
}

int dag_save_to_file(DAG *dag, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;
    
    for (int i = 0; i < dag->num_nodes; i++) {
        for (int j = 0; j < dag->num_nodes; j++) {
            fprintf(file, "%d ", dag->adj_matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 1;
}

DAG* dag_load_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    
    // Count nodes (assuming square matrix)
    int nodes = 0;
    char ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        if (ch == ' ') nodes++;
    }
    nodes++;  // Last number in row
    rewind(file);
    
    DAG *dag = dag_create(nodes);
    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            fscanf(file, "%d", &dag->adj_matrix[i][j]);
        }
    }
    fclose(file);
    return dag;
}




#include "dag.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// Private helper functions
static void shuffle_nodes(int *array, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

static void connect_nodes(DAG *dag, int *order) {
    // Create spanning tree
    for (int i = 1; i < dag->num_nodes; i++) {
        int parent = rand() % i;
        dag->adj_matrix[order[parent]][order[i]] = 1;
    }
}

DAG* dag_create(int num_nodes, float saturation) {
    // Validate input
    if (num_nodes < 1) return NULL;
    float min_sat = (num_nodes-1.0f)/(num_nodes*(num_nodes-1)/2);
    if (saturation < min_sat) {
        fprintf(stderr, "Saturation must be at least %.4f for connectivity\n", min_sat);
        return NULL;
    }

    // Allocate DAG structure
    DAG *dag = malloc(sizeof(DAG));
    dag->num_nodes = num_nodes;
    dag->adj_matrix = malloc(num_nodes * sizeof(int*));
    
    // Initialize adjacency matrix
    for (int i = 0; i < num_nodes; i++) {
        dag->adj_matrix[i] = calloc(num_nodes, sizeof(int));
    }

    // Create random node order
    int *order = malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++) order[i] = i;
    shuffle_nodes(order, num_nodes);

    // Phase 1: Ensure connectivity
    connect_nodes(dag, order);

    // Phase 2: Add remaining edges
    const int total_possible = num_nodes*(num_nodes-1)/2;
    const int target_edges = saturation * total_possible;
    int current_edges = num_nodes - 1;
    
    // Calculate probability for remaining edges
    float p = (target_edges - current_edges) / 
             (float)(total_possible - (num_nodes-1));

    // Add edges probabilistically
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i+1; j < num_nodes; j++) {
            if (!dag->adj_matrix[order[i]][order[j]] && 
               ((float)rand()/RAND_MAX) <= p) {
                dag->adj_matrix[order[i]][order[j]] = 1;
                current_edges++;
            }
        }
    }

    // Cleanup
    free(order);
    return dag;
}

// Rest of file I/O functions...
