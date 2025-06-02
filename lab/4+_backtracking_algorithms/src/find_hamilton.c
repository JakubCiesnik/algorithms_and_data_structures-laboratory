#include <stdbool.h>
#include "graph.h"

SearchState* init_search_state(int vertices, int start_vertex) {
    SearchState *state = malloc(sizeof(SearchState));
    state->visited = malloc(vertices * sizeof(bool));
    state->path = malloc(vertices * sizeof(int));
    state->path_size = 0;
    state->used_count = 0;
    state->start_vertex = start_vertex;
    
    for (int i = 0; i < vertices; i++) {
        state->visited[i] = false;
    }
    return state;
}

void free_search_state(SearchState *state) {
    free(state->visited);
    free(state->path);
    free(state);
}

int next_successor(const Graph *graph, int v, int current) {
    for (int i = current + 1; i < graph->vertices; i++) {
        if (graph->adjacency_matrix[v][i]) {
            return i;
        }
    }
    return -1;
}

bool find_hamiltonian_path(Graph *graph, SearchState *state, int v) {
    state->visited[v] = true;
    state->used_count++;
    
    // Try all successors
    for (int i = next_successor(graph, v, -1); i != -1; i = next_successor(graph, v, i)) {
        if (i == state->start_vertex) {
            if (state->used_count == graph->vertices) {
                state->path[state->path_size++] = v;
                return true;
            }
        }
        
        if (!state->visited[i]) {
            if (find_hamiltonian_path(graph, state, i)) {
                state->path[state->path_size++] = v;
                return true;
            }
        }
    }
    
    // Backtrack
    state->visited[v] = false;
    state->used_count--;
    return false;
}

bool hamiltonian_cycle(Graph *graph, int start_vertex, int **cycle, int *cycle_length) {
    SearchState *state = init_search_state(graph->vertices, start_vertex);
    bool found = find_hamiltonian_path(graph, state, start_vertex);
    
    if (found) {
        // Complete the cycle by adding start vertex at the end
        *cycle_length = graph->vertices + 1;
        *cycle = malloc(*cycle_length * sizeof(int));
        
        // Copy the path in reverse order (from recursive calls)
        for (int i = 0; i < graph->vertices; i++) {
            (*cycle)[i] = state->path[graph->vertices - 1 - i];
        }
        (*cycle)[graph->vertices] = start_vertex;
    }
   
    free_search_state(state);
    return found;
}

// ex2

PathList* create_pathlist(int capacity) {
    PathList *pl = malloc(sizeof(PathList));
    pl->paths = malloc(capacity * sizeof(IntList*));
    pl->count = 0;
    pl->capacity = capacity;
    return pl;
}

void add_to_pathlist(PathList *pl, IntList *path) {
    if (pl->count >= pl->capacity) {
        pl->capacity *= 2;
        pl->paths = realloc(pl->paths, pl->capacity * sizeof(IntList*));
    }
    pl->paths[pl->count++] = path;
}

// Modified recursive function
void find_all_paths(Graph *graph, SearchState *state, int v, PathList *results) {
    state->visited[v] = true;
    state->used_count++;
    
    // Store current node in path
    state->path[state->path_size++] = v;

    // Check if Hamiltonian path is complete
    if (state->used_count == graph->vertices) {
        // Create new IntList and copy path
        IntList *new_path = create_list(state->path_size);
        for (int i = 0; i < state->path_size; i++) {
            new_path->items[i] = state->path[i];
        }
        new_path->size = state->path_size;
        add_to_pathlist(results, new_path);
    }
    else {
        // Continue exploring successors
        for (int i = next_successor(graph, v, -1); i != -1; i = next_successor(graph, v, i)) {
            if (!state->visited[i]) {
                find_all_paths(graph, state, i, results);
            }
        }
    }

    // Backtrack
    state->visited[v] = false;
    state->used_count--;
    state->path_size--;
}

// Main function to find all Hamiltonian paths
PathList* find_all_hamiltonian_paths(Graph *graph, int start_vertex) {
    SearchState *state = init_search_state(graph->vertices, start_vertex);
    PathList *results = create_pathlist(10);

    // Initialize with start vertex
    state->path[state->path_size++] = start_vertex;
    state->visited[start_vertex] = true;
    state->used_count++;

    // Explore all paths starting from start_vertex
    for (int i = next_successor(graph, start_vertex, -1); i != -1; i = next_successor(graph, start_vertex, i)) {
        if (!state->visited[i]) {
            find_all_paths(graph, state, i, results);
        }
    }

    free_search_state(state);
    return results;
}

// // Find Hamilton cycle
// IntList* find_hamilton_cycle_simple(Graph* graph) {
//     if (graph->vertices < 3) return NULL;
//     
//     V = create_list(graph->vertices + 1);
//     cycle_found = false;
//     start_vertex = 0;
//     start_time = clock();
//     timeout_seconds = 2.0; // 2 second timeout
//     
//     hamilton(graph, start_vertex);
//     
//     if (cycle_found) {
//         IntList* result = create_list(V->size);
//         for (int i = 0; i < V->size; i++) {
//             add_to_list(result, V->items[i]);
//         }
//         free_list(V);
//         return result;
//     }
//     
//     free_list(V);
//     return NULL;
// }
//
// // Find Hamilton cycle with configurable timeout
// IntList* find_hamilton_cycle_with_timeout(Graph* graph, double timeout_sec) {
//     if (graph->vertices < 3) return NULL;
//     
//     V = create_list(graph->vertices + 1);
//     cycle_found = false;
//     start_vertex = 0;
//     start_time = clock();
//     timeout_seconds = timeout_sec;
//     
//     hamilton(graph, start_vertex);
//     
//     if (cycle_found) {
//         IntList* result = create_list(V->size);
//         for (int i = 0; i < V->size; i++) {
//             add_to_list(result, V->items[i]);
//         }
//         free_list(V);
//         return result;
//     }
//     
//     free_list(V);
//     return NULL;
// }
// static IntList* V; // lista zawierająca odwiedzone wierzchołki
// static int start_vertex;
// static bool cycle_found;
// static clock_t start_time;
// static double timeout_seconds;
//
// // Hamilton(v) - follows pseudocode exactly
// void hamilton(Graph* graph, int v) {
//     if (cycle_found) return;
//     
//     // Check for timeout
//     clock_t current_time = clock();
//     double elapsed = get_time_diff(start_time, current_time);
//     if (elapsed >= timeout_seconds) {
//         return; // Exit due to timeout
//     }
//     
//     // V.Add(v);
//     add_to_list(V, v);
//     
//     // dla każdego nieodwiedzonego sąsiada w wierzchołka v
//     for (int w = 0; w < graph->vertices; w++) {
//         if (graph->adjacency_matrix[v][w] && !contains(V, w)) {
//             // Hamilton(w);
//             hamilton(graph, w);
//         }
//     }
//     
//     // if V zawiera wszystkie wierzchołki grafu i istnieje krawędź z v do źródła
//     if (V->size == graph->vertices && has_edge(graph, v, start_vertex)) {
//         // cykl znaleziony
//         cycle_found = true;
//         add_to_list(V, start_vertex); // Complete the cycle
//         return;
//     }
//     
//     // else V.Remove(v);
//     if (!cycle_found) {
//         remove_from_list(V, v);
//     }
// }
