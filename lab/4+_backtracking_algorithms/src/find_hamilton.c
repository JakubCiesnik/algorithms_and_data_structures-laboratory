#include "graph.h"

static IntList* V; // lista zawierająca odwiedzone wierzchołki
static int start_vertex;
static bool cycle_found;

// Hamilton(v) - follows pseudocode exactly
void hamilton(Graph* graph, int v) {
    if (cycle_found) return;
    
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
