#include "dag_generator.h"
#include <stdlib.h>
#include <time.h> // For srand

Graph* generate_random_dag(int num_nodes, float saturation) {
    if (num_nodes <= 0 || saturation < 0.0f || saturation > 1.0f) {
        fprintf(stderr, "Invalid parameters for DAG generation.\n");
        return NULL;
    }

    Graph* dag = create_graph(num_nodes, true, false); // Directed, unweighted
    if (!dag) return NULL;

    // Create a random permutation of nodes to define a topological order
    int* order = (int*)malloc(num_nodes * sizeof(int));
    if(!order) { free_graph(dag); return NULL; }
    for (int i = 0; i < num_nodes; i++) {
        order[i] = i;
    }
    // Fisher-Yates shuffle
    for (int i = num_nodes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }

    long long max_possible_edges = (long long)num_nodes * (num_nodes - 1) / 2;
    if (num_nodes <=1) max_possible_edges = 0;

    long long target_edges = (long long)(saturation * max_possible_edges);
    long long current_edges = 0;

    // Add edges respecting the random topological order (order[i] -> order[j] only if i < j)
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i + 1; j < num_nodes; j++) {
            // Decide whether to add this edge
            // A simple approach: if we still need edges and a random chance passes
            if (current_edges < target_edges) {
                // Ensure not to overshoot target_edges too much with a simple probability
                // Or, more deterministically, fill until target_edges is met if possible
                // For a more uniform distribution of edges given saturation:
                if (max_possible_edges > 0 && (double)rand() / RAND_MAX < (double)(target_edges - current_edges) / (max_possible_edges - current_edges + 1) ) {
                     add_edge(dag, order[i], order[j], 1); // weight 1 for unweighted
                     current_edges++;
                }
            } else if (saturation == 1.0 && max_possible_edges > 0) { // Ensure all edges for 100% saturation
                 add_edge(dag, order[i], order[j], 1);
                 current_edges++;
            }
        }
    }
    // If not enough edges were added (e.g. due to randomness for low saturation),
    // one could iterate again or use a more direct selection method.
    // For simplicity, this approach is used.

    free(order);
    return dag;
}