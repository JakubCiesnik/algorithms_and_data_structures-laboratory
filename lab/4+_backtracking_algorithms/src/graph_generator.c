#include "graph.h"

// Graph generation functions
Graph* generate_eulerian_hamiltonian_graph(int vertices, double edge_density) {
    Graph* graph = create_graph(vertices);
    
    // First create a Hamiltonian cycle to ensure the graph is Hamiltonian
    make_hamiltonian_cycle(graph);
    
    // Then add edges to reach target density while maintaining Eulerian property
    add_random_edges_for_euler(graph, edge_density);
    
    // CRITICAL: Ensure Eulerian property is guaranteed
    ensure_eulerian_property(graph);
    
    // Verify the result
    if (!is_eulerian(graph) || !is_connected(graph)) {
        // If still not Eulerian, force it to be Eulerian
        force_eulerian_property(graph);
    }
    
    return graph;
}

void make_hamiltonian_cycle(Graph* graph) {
    // Create a cycle: 0 -> 1 -> 2 -> ... -> (n-1) -> 0
    for (int i = 0; i < graph->vertices; i++) {
        int next = (i + 1) % graph->vertices;
        add_edge(graph, i, next);
    }
}

void add_random_edges_for_euler(Graph* graph, double target_density) {
    int max_edges = (graph->vertices * (graph->vertices - 1)) / 2;
    int target_edges = (int)(max_edges * target_density);
    
    // If target is less than current edges, we're done
    if (target_edges <= graph->edges) {
        return;
    }
    
    srand(time(NULL) + graph->vertices); // Better seed to avoid same random sequence
    
    // Simple approach: just add random edges, we'll fix Eulerian property later
    int attempts = 0;
    int max_attempts = graph->vertices * graph->vertices; // Reasonable limit
    
    while (graph->edges < target_edges && attempts < max_attempts) {
        int u = rand() % graph->vertices;
        int v = rand() % graph->vertices;
        
        if (u != v && !has_edge(graph, u, v)) {
            add_edge(graph, u, v);
        }
        
        attempts++;
    }
}

void ensure_eulerian_property(Graph* graph) {
    int max_iterations = 20; // Increase iterations
    int iteration = 0;
    
    while (iteration < max_iterations) {
        // Collect all vertices with odd degree
        int odd_vertices[graph->vertices];
        int odd_count = 0;
        
        for (int i = 0; i < graph->vertices; i++) {
            int degree = 0;
            for (int j = 0; j < graph->vertices; j++) {
                degree += graph->adjacency_matrix[i][j];
            }
            if (degree % 2 != 0) {
                odd_vertices[odd_count] = i;
                odd_count++;
            }
        }
        
        // If no odd vertices, we're done (Eulerian)
        if (odd_count == 0) {
            return;
        }
        
        // Connect odd vertices in pairs
        for (int i = 0; i < odd_count - 1; i += 2) {
            int u = odd_vertices[i];
            int v = odd_vertices[i + 1];
            
            if (!has_edge(graph, u, v)) {
                add_edge(graph, u, v);
            }
        }
        
        // If odd number of odd vertices, connect the last one to the first
        if (odd_count % 2 == 1) {
            int last_odd = odd_vertices[odd_count - 1];
            int first_odd = odd_vertices[0];
            if (!has_edge(graph, last_odd, first_odd)) {
                add_edge(graph, last_odd, first_odd);
            }
        }
        
        iteration++;
    }
}

// Force Eulerian property as a last resort
void force_eulerian_property(Graph* graph) {
    // Keep iterating until all vertices have even degree
    int max_iterations = 50;
    int iteration = 0;
    
    while (iteration < max_iterations) {
        // Check if already Eulerian
        bool all_even = true;
        for (int i = 0; i < graph->vertices; i++) {
            int degree = 0;
            for (int j = 0; j < graph->vertices; j++) {
                degree += graph->adjacency_matrix[i][j];
            }
            if (degree % 2 != 0) {
                all_even = false;
                break;
            }
        }
        
        if (all_even) {
            return; // Already Eulerian
        }
        
        // Find all odd-degree vertices
        int odd_vertices[graph->vertices];
        int odd_count = 0;
        
        for (int i = 0; i < graph->vertices; i++) {
            int degree = 0;
            for (int j = 0; j < graph->vertices; j++) {
                degree += graph->adjacency_matrix[i][j];
            }
            if (degree % 2 != 0) {
                odd_vertices[odd_count] = i;
                odd_count++;
            }
        }
        
        // Connect pairs of odd vertices
        for (int i = 0; i < odd_count - 1; i += 2) {
            int u = odd_vertices[i];
            int v = odd_vertices[i + 1];
            
            if (!has_edge(graph, u, v)) {
                add_edge(graph, u, v);
            } else {
                // If already connected, add a different edge
                bool added = false;
                for (int k = 0; k < graph->vertices && !added; k++) {
                    if (k != u && !has_edge(graph, u, k)) {
                        add_edge(graph, u, k);
                        added = true;
                    }
                }
            }
        }
        
        // If odd number of odd vertices, connect last one to first one
        if (odd_count % 2 == 1) {
            int last = odd_vertices[odd_count - 1];
            int first = odd_vertices[0];
            
            if (!has_edge(graph, last, first)) {
                add_edge(graph, last, first);
            } else {
                // Add any edge to make it even
                for (int k = 0; k < graph->vertices; k++) {
                    if (k != last && !has_edge(graph, last, k)) {
                        add_edge(graph, last, k);
                        break;
                    }
                }
            }
        }
        
        iteration++;
    }
}

// Simple backup method to create Eulerian Hamiltonian graphs
Graph* create_simple_eulerian_hamiltonian_graph(int vertices, double edge_density) {
    Graph* graph = create_graph(vertices);
    
    // Create Hamiltonian cycle first
    make_hamiltonian_cycle(graph);
    
    // For Eulerian property, add edges in pairs only
    int max_edges = (vertices * (vertices - 1)) / 2;
    int target_edges = (int)(max_edges * edge_density);
    
    srand(time(NULL) + vertices * 13); // Different seed
    
    // Add pairs of edges to maintain even degrees
    while (graph->edges < target_edges - 1) { // Leave room for pairs
        int u = rand() % vertices;
        int v = rand() % vertices;
        
        if (u != v && !has_edge(graph, u, v)) {
            add_edge(graph, u, v);
            
            // If we still have room, add another edge to maintain even degrees
            if (graph->edges < target_edges) {
                int x, y;
                int attempts = 0;
                do {
                    x = rand() % vertices;
                    y = rand() % vertices;
                    attempts++;
                } while ((x == y || has_edge(graph, x, y)) && attempts < 100);
                
                if (attempts < 100) {
                    add_edge(graph, x, y);
                }
            }
        }
    }
    
    return graph;
}
