#include "def_graph.h"
#include <stdlib.h>
#include <stdio.h>

// creates a graph of given size and properties, does not populate it
Graph* create_graph(int num_nodes, bool is_directed, bool is_weighted) {
    if (num_nodes <= 0) return NULL; // precondition checks

    Graph* graph = (Graph*)malloc(sizeof(Graph)); // initialize graph instance
    if (!graph) return NULL; // malloc failed

    graph->num_nodes = num_nodes; 
    graph->is_directed = is_directed;
    graph->is_weighted = is_weighted;

    // Adjacency Matrix
    graph->adj_matrix = (int**)malloc(num_nodes * sizeof(int*)); // malloc the frame
    if (!graph->adj_matrix) { // malloc failed, clean
        free(graph);
        return NULL;
    }
    for (int i = 0; i < num_nodes; i++) {
        graph->adj_matrix[i] = (int*)calloc(num_nodes, sizeof(int)); // Initialize with 0
        if (!graph->adj_matrix[i]) { // calloc failed, clean
            for(int k=0; k<i; ++k) free(graph->adj_matrix[k]);
            free(graph->adj_matrix);
            free(graph);
            return NULL;
        }
    }
    
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    if ( // precondition checks; any of:
      !graph ||                    // graph doesn't exist
      src < 0 ||                  // src under range
      src >= graph->num_nodes || // src over range
      dest < 0 ||               // dest under range
      dest >= graph->num_nodes // dest over range
      ) {
        fprintf(stderr, "Error: Invalid node or graph in add_edge.\n");
        return;
    }

    int edge_weight = graph->is_weighted ? weight : 1;

    // Add to Adjacency Matrix
    graph->adj_matrix[src][dest] = edge_weight;
    if (!graph->is_directed) {
        graph->adj_matrix[dest][src] = edge_weight;
    }
}

void free_graph(Graph* graph) {
    if (!graph) return;

    // Free Adjacency Matrix
    if (graph->adj_matrix) {
        for (int i = 0; i < graph->num_nodes; i++) {
            free(graph->adj_matrix[i]);
        }
        free(graph->adj_matrix);
    }

    free(graph);
}

void print_graph_matrix(const Graph* graph) {
    if (!graph) return;
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < graph->num_nodes; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}
