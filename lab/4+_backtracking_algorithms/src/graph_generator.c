#include "graph.h"

// Generate Eulerian + Hamiltonian graph
Graph* generate_eulerian_hamiltonian_graph(int vertices, double edge_density) {
    Graph* graph = create_graph(vertices);
    srand(time(NULL) + vertices);
    
    // 1. Create Hamilton cycle
    make_hamiltonian_cycle(graph);
    
    // print_graph(graph); // DEBUG

    // 2. Add triangles for density (euler)
    add_triangles_for_density(graph, edge_density);
    
    // print_graph(graph); // DEBUG

    // 3. Randomize to hide obvious cycle (make hamilton not too fast)
    randomize_vertex_ordering(graph);
    
    // print_graph(graph); // DEBUG

    return graph;
}

// Create basic Hamilton cycle: 0->1->2->...->n-1->0
void make_hamiltonian_cycle(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        int next = (i + 1) % graph->vertices;
        add_edge(graph, i, next);
    }
}

// Add triangles to increase density while keeping Eulerian property
void add_triangles_for_density(Graph* graph, double edge_density) {
    int max_edges = (graph->vertices * (graph->vertices - 1)) / 2;
    int target_edges = (int)(max_edges * edge_density);
    
    if (graph->edges >= target_edges) return;
    
    int attempts = 0;
    int max_attempts = graph->vertices * graph->vertices;
    
    // Add complete triangles (3 new edges at once)
    while (graph->edges + 3 <= target_edges && attempts < max_attempts) {
        int v1 = rand() % graph->vertices;
        int v2 = rand() % graph->vertices;
        int v3 = rand() % graph->vertices;
        
        if (v1 != v2 && v2 != v3 && v1 != v3) {
            if (try_add_triangle(graph, v1, v2, v3)) {
                continue;
            }
        }
        attempts++;
    }
}

bool try_add_triangle(Graph* graph, int v1, int v2, int v3) {
    // Check if all three edges of the triangle don't exist yet
    bool edge1_new = !has_edge(graph, v1, v2);
    bool edge2_new = !has_edge(graph, v2, v3);
    bool edge3_new = !has_edge(graph, v3, v1);
    
    // We need all three edges to be new to form a proper triangle
    if (edge1_new && edge2_new && edge3_new) {
        add_edge(graph, v1, v2);
        add_edge(graph, v2, v3);
        add_edge(graph, v3, v1);
        return true;
    }
    
    return false;
}

// Swap two vertices in adjacency matrix
void swap_vertices(Graph* graph, int v1, int v2) {
    if (v1 == v2 || v1 >= graph->vertices || v2 >= graph->vertices) {
        return;
    }
    
    // Swap rows
    int* temp_row = graph->adjacency_matrix[v1];
    graph->adjacency_matrix[v1] = graph->adjacency_matrix[v2];
    graph->adjacency_matrix[v2] = temp_row;
    
    // Swap columns
    for (int i = 0; i < graph->vertices; i++) {
        int temp = graph->adjacency_matrix[i][v1];
        graph->adjacency_matrix[i][v1] = graph->adjacency_matrix[i][v2];
        graph->adjacency_matrix[i][v2] = temp;
    }
}

// Randomize vertex ordering to hide obvious Hamilton cycle
void randomize_vertex_ordering(Graph* graph) {
    int num_swaps = graph->vertices * 2;
    
    for (int i = 0; i < num_swaps; i++) {
        int v1 = rand() % graph->vertices;
        int v2 = rand() % graph->vertices;
        
        if (v1 != v2) {
            swap_vertices(graph, v1, v2);
        }
    }
}
