#include "topological_sort.h"
#include <stdlib.h>
#include <stdio.h> // For fprintfs

// --- Helper for Adjacency Matrix ---
// visited: 0 = not visited, 1 = visiting (on stack), 2 = visited (finished)
// stack_idx is the current index to insert into sorted_order_result (filled from end)
static bool topo_dfs_matrix(Graph* graph, int u, int* visited, int* sorted_order_result, int* stack_idx) {
    visited[u] = 1; // Mark as visiting

    for (int v = 0; v < graph->num_nodes; v++) {
        if (graph->adj_matrix[u][v] != 0) { // If there is an edge u -> v
            if (visited[v] == 1) {
                return false; // Cycle detected
            }
            if (visited[v] == 0) {
                if (!topo_dfs_matrix(graph, v, visited, sorted_order_result, stack_idx)) {
                    return false; // Cycle detected in deeper DFS
                }
            }
        }
    }

    visited[u] = 2; // Mark as visited
    sorted_order_result[(*stack_idx)--] = u; // Add to sorted list (from end)
    return true;
}

bool topological_sort_matrix(Graph* graph, int* sorted_order_result) {
    if (!graph || !graph->is_directed) {
        fprintf(stderr, "Topological sort requires a directed graph.\n");
        return false;
    }

    int* visited = (int*)calloc(graph->num_nodes, sizeof(int));
    if (!visited) {
        fprintf(stderr, "Memory allocation failed for visited array.\n");
        return false;
    }
    
    int stack_idx = graph->num_nodes - 1;

    for (int i = 0; i < graph->num_nodes; i++) {
        if (visited[i] == 0) {
            if (!topo_dfs_matrix(graph, i, visited, sorted_order_result, &stack_idx)) {
                free(visited);
                fprintf(stderr, "Cycle detected in graph. Not a DAG.\n");
                return false; // Cycle detected
            }
        }
    }

    free(visited);
    return true;
}


// --- Helper for Adjacency List ---
static bool topo_dfs_list(Graph* graph, int u, int* visited, int* sorted_order_result, int* stack_idx) {
    visited[u] = 1; // Mark as visiting

    AdjListNode* node = graph->adj_list_array[u];
    while (node) {
        int v = node->dest;
        if (visited[v] == 1) {
            return false; // Cycle detected
        }
        if (visited[v] == 0) {
            if (!topo_dfs_list(graph, v, visited, sorted_order_result, stack_idx)) {
                return false; // Cycle detected in deeper DFS
            }
        }
        node = node->next;
    }

    visited[u] = 2; // Mark as visited
    sorted_order_result[(*stack_idx)--] = u; // Add to sorted list (from end)
    return true;
}

bool topological_sort_list(Graph* graph, int* sorted_order_result) {
    if (!graph || !graph->is_directed) {
        fprintf(stderr, "Topological sort requires a directed graph.\n");
        return false;
    }

    int* visited = (int*)calloc(graph->num_nodes, sizeof(int));
     if (!visited) {
        fprintf(stderr, "Memory allocation failed for visited array.\n");
        return false;
    }
    int stack_idx = graph->num_nodes - 1;

    for (int i = 0; i < graph->num_nodes; i++) {
        if (visited[i] == 0) {
            if (!topo_dfs_list(graph, i, visited, sorted_order_result, &stack_idx)) {
                free(visited);
                fprintf(stderr, "Cycle detected in graph. Not a DAG.\n");
                return false; // Cycle detected
            }
        }
    }

    free(visited);
    return true;
}