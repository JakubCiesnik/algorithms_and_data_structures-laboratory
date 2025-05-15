#include "undirected_graph_generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // For srand

Graph* generate_random_undirected_graph(int num_nodes, float saturation, int min_weight, int max_weight) {
    if (num_nodes <= 0 || saturation < 0.0f || saturation > 1.0f || min_weight > max_weight) {
        fprintf(stderr, "Invalid parameters for undirected graph generation.\n");
        return NULL;
    }

    Graph* graph = create_graph(num_nodes, false, true); // Undirected, weighted
    if (!graph) return NULL;

    // Ensure connectivity by creating a spanning tree (e.g., a path graph initially)
    // This also helps ensure the graph is connected for MST.
    if (num_nodes > 1) {
        // Create a random permutation for connecting nodes in a path to ensure connectivity
        int* p = (int*)malloc(num_nodes * sizeof(int));
        if(!p) { free_graph(graph); return NULL; }
        for(int i=0; i<num_nodes; ++i) p[i] = i;
        for(int i=num_nodes-1; i>0; --i) {
            int j = rand() % (i+1);
            int temp = p[i]; p[i] = p[j]; p[j] = temp;
        }
        for (int i = 0; i < num_nodes - 1; ++i) {
            int weight = min_weight + rand() % (max_weight - min_weight + 1);
            add_edge(graph, p[i], p[i+1], weight);
        }
        free(p);
    }
    
    long long current_edges = num_nodes > 1 ? num_nodes - 1 : 0;
    long long max_possible_edges = (long long)num_nodes * (num_nodes - 1) / 2;
    if (num_nodes <=1) max_possible_edges = 0;
    long long target_edges = (long long)(saturation * max_possible_edges);
    if (target_edges < current_edges) target_edges = current_edges; // Must at least have spanning tree edges

    // Add remaining edges randomly
    // Keep track of existing edges to avoid duplicates and self-loops (already handled by i < j)
    // The add_edge function handles both matrix and list, and undirected nature.
    // We only need to iterate over unique pairs (i, j) where i < j.
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = i + 1; j < num_nodes; ++j) {
            if (graph->adj_matrix[i][j] == 0) { // If no edge exists yet
                if (current_edges < target_edges) {
                     // Simplified probability for adding more edges
                    if (max_possible_edges > 0 && (double)rand() / RAND_MAX < (double)(target_edges - current_edges) / (max_possible_edges - current_edges +1) ) {
                        int weight = min_weight + rand() % (max_weight - min_weight + 1);
                        add_edge(graph, i, j, weight);
                        current_edges++;
                    }
                } else if (saturation == 1.0 && max_possible_edges > 0) { // Ensure all edges for 100% saturation
                    int weight = min_weight + rand() % (max_weight - min_weight + 1);
                    add_edge(graph, i, j, weight);
                    current_edges++;
                }
            }
        }
    }
    return graph;
}