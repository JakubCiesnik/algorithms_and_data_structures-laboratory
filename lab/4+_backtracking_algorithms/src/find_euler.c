#include "graph.h"

static IntList* C; // lista zawierająca wierzchołki tworzące cykl

// Euler(v) - follows pseudocode exactly
void euler(Graph* graph, int v, bool **visited_edges) {
    // dla każdego wierzchołka w takiego, że istnieje nieodwiedzona krawędź z v do w
    for (int w = 0; w < graph->vertices; w++) {
        if (graph->adjacency_matrix[v][w] && !visited_edges[v][w]) {
            // odwiedź krawędź {v, w}
            visited_edges[v][w] = true;
            visited_edges[w][v] = true;
            
            // Euler(w);
            euler(graph, w, visited_edges);
        }
    }
    
    // C.Add(v);
    add_to_list(C, v);
}

// Find Euler cycle
IntList* find_euler_cycle_simple(Graph* graph) {
    if (!is_eulerian(graph)) return NULL;
    
    C = create_list(graph->edges + graph->vertices);
    
    bool **visited_edges = (bool**)malloc(graph->vertices * sizeof(bool*));
    for (int i = 0; i < graph->vertices; i++) {
        visited_edges[i] = (bool*)calloc(graph->vertices, sizeof(bool));
    }
    
    euler(graph, 0, visited_edges);
    
    for (int i = 0; i < graph->vertices; i++) {
        free(visited_edges[i]);
    }
    free(visited_edges);
    
    return C;
}
