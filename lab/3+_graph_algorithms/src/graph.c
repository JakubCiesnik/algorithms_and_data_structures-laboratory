#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* create_graph(int num_nodes, bool is_directed, bool is_weighted) {
    if (num_nodes <= 0) return NULL;

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->num_nodes = num_nodes;
    graph->is_directed = is_directed;
    graph->is_weighted = is_weighted;

    // Adjacency Matrix
    graph->adj_matrix = (int**)malloc(num_nodes * sizeof(int*));
    if (!graph->adj_matrix) {
        free(graph);
        return NULL;
    }
    for (int i = 0; i < num_nodes; i++) {
        graph->adj_matrix[i] = (int*)calloc(num_nodes, sizeof(int)); // Initialize with 0
        if (!graph->adj_matrix[i]) {
            // Free previously allocated rows and graph
            for(int k=0; k<i; ++k) free(graph->adj_matrix[k]);
            free(graph->adj_matrix);
            free(graph);
            return NULL;
        }
    }

    // Adjacency List
    graph->adj_list_array = (AdjListNode**)malloc(num_nodes * sizeof(AdjListNode*));
    if (!graph->adj_list_array) {
        for(int i=0; i<num_nodes; ++i) free(graph->adj_matrix[i]);
        free(graph->adj_matrix);
        free(graph);
        return NULL;
    }
    for (int i = 0; i < num_nodes; i++) {
        graph->adj_list_array[i] = NULL; // Initialize heads to NULL
    }

    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->num_nodes || dest < 0 || dest >= graph->num_nodes) {
        fprintf(stderr, "Error: Invalid node or graph in add_edge.\n");
        return;
    }

    int edge_weight = graph->is_weighted ? weight : 1;

    // Add to Adjacency Matrix
    graph->adj_matrix[src][dest] = edge_weight;
    if (!graph->is_directed) {
        graph->adj_matrix[dest][src] = edge_weight;
    }

    // Add to Adjacency List for src -> dest
    AdjListNode* newNodeDest = (AdjListNode*)malloc(sizeof(AdjListNode));
    if(!newNodeDest) { fprintf(stderr, "Memory allocation failed for adj list node\n"); return; }
    newNodeDest->dest = dest;
    newNodeDest->weight = edge_weight;
    newNodeDest->next = graph->adj_list_array[src];
    graph->adj_list_array[src] = newNodeDest;

    if (!graph->is_directed) {
        // Add to Adjacency List for dest -> src
        AdjListNode* newNodeSrc = (AdjListNode*)malloc(sizeof(AdjListNode));
        if(!newNodeSrc) { fprintf(stderr, "Memory allocation failed for adj list node\n"); return; }
        newNodeSrc->dest = src;
        newNodeSrc->weight = edge_weight;
        newNodeSrc->next = graph->adj_list_array[dest];
        graph->adj_list_array[dest] = newNodeSrc;
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

    // Free Adjacency List
    if (graph->adj_list_array) {
        for (int i = 0; i < graph->num_nodes; i++) {
            AdjListNode* current = graph->adj_list_array[i];
            while (current) {
                AdjListNode* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adj_list_array);
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

void print_graph_list(const Graph* graph) {
    if (!graph) return;
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->num_nodes; i++) {
        printf("Node %d: ", i);
        AdjListNode* current = graph->adj_list_array[i];
        while (current) {
            printf("-> %d", current->dest);
            if (graph->is_weighted) {
                printf("(w:%d)", current->weight);
            }
            current = current->next;
        }
        printf("\n");
    }
}