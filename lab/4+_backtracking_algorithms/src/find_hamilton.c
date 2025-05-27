#include "graph.h"

static IntList* V; // lista zawierająca odwiedzone wierzchołki
static int start_vertex;
static bool cycle_found;
static clock_t start_time;
static double timeout_seconds;

// Hamilton(v) - follows pseudocode exactly
void hamilton(Graph* graph, int v) {
    if (cycle_found) return;
    
    // Check for timeout
    clock_t current_time = clock();
    double elapsed = get_time_diff(start_time, current_time);
    if (elapsed >= timeout_seconds) {
        return; // Exit due to timeout
    }
    
    // V.Add(v);
    add_to_list(V, v);
    
    // dla każdego nieodwiedzonego sąsiada w wierzchołka v
    for (int w = 0; w < graph->vertices; w++) {
        if (graph->adjacency_matrix[v][w] && !contains(V, w)) {
            // Hamilton(w);
            hamilton(graph, w);
        }
    }
    
    // if V zawiera wszystkie wierzchołki grafu i istnieje krawędź z v do źródła
    if (V->size == graph->vertices && has_edge(graph, v, start_vertex)) {
        // cykl znaleziony
        cycle_found = true;
        add_to_list(V, start_vertex); // Complete the cycle
        return;
    }
    
    // else V.Remove(v);
    if (!cycle_found) {
        remove_from_list(V, v);
    }
}

// Find Hamilton cycle
IntList* find_hamilton_cycle_simple(Graph* graph) {
    if (graph->vertices < 3) return NULL;
    
    V = create_list(graph->vertices + 1);
    cycle_found = false;
    start_vertex = 0;
    start_time = clock();
    timeout_seconds = 2.0; // 2 second timeout
    
    hamilton(graph, start_vertex);
    
    if (cycle_found) {
        IntList* result = create_list(V->size);
        for (int i = 0; i < V->size; i++) {
            add_to_list(result, V->items[i]);
        }
        free_list(V);
        return result;
    }
    
    free_list(V);
    return NULL;
}

// Find Hamilton cycle with configurable timeout
IntList* find_hamilton_cycle_with_timeout(Graph* graph, double timeout_sec) {
    if (graph->vertices < 3) return NULL;
    
    V = create_list(graph->vertices + 1);
    cycle_found = false;
    start_vertex = 0;
    start_time = clock();
    timeout_seconds = timeout_sec;
    
    hamilton(graph, start_vertex);
    
    if (cycle_found) {
        IntList* result = create_list(V->size);
        for (int i = 0; i < V->size; i++) {
            add_to_list(result, V->items[i]);
        }
        free_list(V);
        return result;
    }
    
    free_list(V);
    return NULL;
}
