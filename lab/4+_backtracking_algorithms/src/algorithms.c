#include "graph.h"

#define HAMILTON_TIMEOUT_SECONDS 5.0  // 5 second timeout for Hamilton cycle

// Global variables for timeout
static clock_t hamilton_start_time;
static bool hamilton_timeout_reached;

// Euler cycle algorithm based on pseudocode
IntList* find_euler_cycle(Graph* graph) {
    if (!is_eulerian(graph)) {
        return NULL;
    }
    
    IntList* cycle = create_list(graph->edges + graph->vertices);
    
    // Create a copy of the graph to track visited edges
    bool **visited_edges = (bool**)malloc(graph->vertices * sizeof(bool*));
    for (int i = 0; i < graph->vertices; i++) {
        visited_edges[i] = (bool*)calloc(graph->vertices, sizeof(bool));
    }
    
    // Start from vertex 0
    euler_recursive(graph, 0, visited_edges, cycle);
    
    // Free visited edges matrix
    for (int i = 0; i < graph->vertices; i++) {
        free(visited_edges[i]);
    }
    free(visited_edges);
    
    return cycle;
}

void euler_recursive(Graph* graph, int v, bool **visited_edges, IntList* cycle) {
    // For each neighbor w such that edge {v, w} is not visited (line 4-8 of pseudocode)
    for (int w = 0; w < graph->vertices; w++) {
        if (graph->adjacency_matrix[v][w] && !visited_edges[v][w]) {
            // Visit edge {v, w} (line 6)
            visited_edges[v][w] = true;
            visited_edges[w][v] = true;
            
            // Recursive call Euler(w) (line 7)
            euler_recursive(graph, w, visited_edges, cycle);
        }
    }
    
    // Add current vertex to cycle C (line 9)
    add_to_list(cycle, v);
}

// Global variable to track if Hamilton cycle was found
static bool hamilton_cycle_found = false;
static IntList* hamilton_result = NULL;

// Hamilton cycle algorithm with backtracking based on pseudocode
IntList* find_hamilton_cycle(Graph* graph) {
    if (graph->vertices < 3) {
        return NULL;
    }
    
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    
    // Initialize timeout and cycle found flag
    hamilton_start_time = clock();
    hamilton_timeout_reached = false;
    hamilton_cycle_found = false;
    
    if (hamilton_result) {
        free_list(hamilton_result);
    }
    hamilton_result = create_list(graph->vertices + 1);
    
    hamilton_recursive_v2(graph, 0, 0, visited);
    
    free(visited);
    
    if (hamilton_cycle_found && !hamilton_timeout_reached) {
        IntList* result = create_list(hamilton_result->size);
        for (int i = 0; i < hamilton_result->size; i++) {
            add_to_list(result, hamilton_result->items[i]);
        }
        return result;
    } else {
        return NULL;
    }
}

void hamilton_recursive_v2(Graph* graph, int v, int start, bool* visited) {
    // Check timeout
    clock_t current_time = clock();
    double elapsed = get_time_diff(hamilton_start_time, current_time);
    if (elapsed > HAMILTON_TIMEOUT_SECONDS) {
        hamilton_timeout_reached = true;
        return;
    }
    
    if (hamilton_cycle_found) {
        return; // Already found a cycle
    }
    
    // V.Add(v) - line 6 of pseudocode
    visited[v] = true;
    add_to_list(hamilton_result, v);
    
    // For each unvisited neighbor w of vertex v - line 7-10 of pseudocode
    for (int w = 0; w < graph->vertices; w++) {
        if (graph->adjacency_matrix[v][w] && !visited[w]) {
            hamilton_recursive_v2(graph, w, start, visited);
        }
    }
    
    // Check if V contains all vertices and there's edge to source - line 11-14
    if (hamilton_result->size == graph->vertices && graph->adjacency_matrix[v][start]) {
        // Cycle found - complete the cycle
        add_to_list(hamilton_result, start);
        hamilton_cycle_found = true;
        return;
    }
    
    // V.Remove(v) - line 17 (backtrack)
    if (!hamilton_cycle_found) {
        hamilton_result->size--; // Remove current vertex
        visited[v] = false;
    }
}
