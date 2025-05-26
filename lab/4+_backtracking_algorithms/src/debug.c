#include "graph.h"

void test_graph_properties(Graph* graph, const char* graph_name) {
    printf("\n=== Testing %s ===\n", graph_name);
    printf("Vertices: %d, Edges: %d\n", graph->vertices, graph->edges);
    
    // Calculate edge density
    int max_edges = (graph->vertices * (graph->vertices - 1)) / 2;
    double density = (double)graph->edges / max_edges;
    printf("Edge density: %.2f%% (%d/%d edges)\n", density * 100, graph->edges, max_edges);
    
    // Test connectivity
    bool connected = is_connected(graph);
    printf("Connected: %s\n", connected ? "YES" : "NO");
    
    // Test Eulerian property
    bool eulerian = is_eulerian(graph);
    printf("Eulerian: %s\n", eulerian ? "YES" : "NO");
    
    // Test Hamiltonian property (basic check)
    bool hamiltonian = is_hamiltonian_naive(graph);
    printf("Hamiltonian: %s\n", hamiltonian ? "YES" : "NO");
    
    // Print degree sequence
    printf("Degree sequence: ");
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->vertices; j++) {
            degree += graph->adjacency_matrix[i][j];
        }
        printf("%d ", degree);
    }
    printf("\n");
    
    if (graph->vertices <= 8) {
        print_graph(graph);
    }
}

void test_euler_algorithm(Graph* graph, const char* graph_name) {
    printf("\n=== Testing Euler Algorithm on %s ===\n", graph_name);
    
    clock_t start = clock();
    IntList* euler_cycle = find_euler_cycle(graph);
    clock_t end = clock();
    
    if (euler_cycle) {
        printf("Euler cycle found in %.6f seconds!\n", get_time_diff(start, end));
        printf("Cycle length: %d\n", euler_cycle->size);
        
        if (euler_cycle->size <= 20) {
            printf("Cycle: ");
            print_list(euler_cycle);
        }
        
        // Verify the cycle
        bool valid = true;
        for (int i = 0; i < euler_cycle->size - 1; i++) {
            int u = euler_cycle->items[i];
            int v = euler_cycle->items[i + 1];
            if (!has_edge(graph, u, v)) {
                printf("ERROR: Invalid edge %d -> %d in cycle!\n", u, v);
                valid = false;
            }
        }
        printf("Cycle validation: %s\n", valid ? "VALID" : "INVALID");
        
        free_list(euler_cycle);
    } else {
        printf("No Euler cycle found (took %.6f seconds)\n", get_time_diff(start, end));
    }
}

void test_hamilton_algorithm(Graph* graph, const char* graph_name) {
    printf("\n=== Testing Hamilton Algorithm on %s ===\n", graph_name);
    
    clock_t start = clock();
    IntList* hamilton_cycle = find_hamilton_cycle(graph);
    clock_t end = clock();
    
    if (hamilton_cycle) {
        printf("Hamilton cycle found in %.6f seconds!\n", get_time_diff(start, end));
        printf("Cycle length: %d\n", hamilton_cycle->size);
        
        if (hamilton_cycle->size <= 20) {
            printf("Cycle: ");
            print_list(hamilton_cycle);
        }
        
        // Verify the cycle
        bool valid = true;
        if (hamilton_cycle->size != graph->vertices + 1) {
            printf("ERROR: Cycle length should be %d, but is %d\n", 
                   graph->vertices + 1, hamilton_cycle->size);
            valid = false;
        } else {
            // Check if first and last vertices are the same
            if (hamilton_cycle->items[0] != hamilton_cycle->items[hamilton_cycle->size - 1]) {
                printf("ERROR: Cycle doesn't start and end at same vertex!\n");
                valid = false;
            }
            
            // Check if all edges exist
            for (int i = 0; i < hamilton_cycle->size - 1; i++) {
                int u = hamilton_cycle->items[i];
                int v = hamilton_cycle->items[i + 1];
                if (!has_edge(graph, u, v)) {
                    printf("ERROR: Invalid edge %d -> %d in cycle!\n", u, v);
                    valid = false;
                }
            }
            
            // Check if all vertices are visited exactly once (except start/end)
            bool* vertex_visited = (bool*)calloc(graph->vertices, sizeof(bool));
            for (int i = 0; i < hamilton_cycle->size - 1; i++) {
                int v = hamilton_cycle->items[i];
                if (vertex_visited[v]) {
                    printf("ERROR: Vertex %d visited multiple times!\n", v);
                    valid = false;
                } else {
                    vertex_visited[v] = true;
                }
            }
            
            for (int i = 0; i < graph->vertices; i++) {
                if (!vertex_visited[i]) {
                    printf("ERROR: Vertex %d not visited!\n", i);
                    valid = false;
                }
            }
            
            free(vertex_visited);
        }
        
        printf("Cycle validation: %s\n", valid ? "VALID" : "INVALID");
        free_list(hamilton_cycle);
    } else {
        printf("No Hamilton cycle found (took %.6f seconds)\n", get_time_diff(start, end));
    }
}

int main() {
    printf("=== Debug: Testing Graph Generation and Algorithms ===\n");
    
    // Test with small graphs first
    int test_sizes[] = {4, 5, 6, 8};
    
    for (int i = 0; i < 4; i++) {
        int n = test_sizes[i];
        
        printf("\n" "================================================\n");
        printf("Testing with %d vertices\n", n);
        printf("================================================\n");
        
        // Generate sparse graph (30%)
        Graph* sparse_graph = generate_eulerian_hamiltonian_graph(n, 0.3);
        char sparse_name[50];
        sprintf(sparse_name, "Sparse Graph (n=%d, 30%%)", n);
        
        test_graph_properties(sparse_graph, sparse_name);
        test_euler_algorithm(sparse_graph, sparse_name);
        test_hamilton_algorithm(sparse_graph, sparse_name);
        
        // Generate dense graph (70%)
        Graph* dense_graph = generate_eulerian_hamiltonian_graph(n, 0.7);
        char dense_name[50];
        sprintf(dense_name, "Dense Graph (n=%d, 70%%)", n);
        
        test_graph_properties(dense_graph, dense_name);
        test_euler_algorithm(dense_graph, dense_name);
        test_hamilton_algorithm(dense_graph, dense_name);
        
        free_graph(sparse_graph);
        free_graph(dense_graph);
    }
    
    printf("\n=== Testing Edge Cases ===\n");
    
    // Test very small graph
    Graph* tiny_graph = create_graph(3);
    add_edge(tiny_graph, 0, 1);
    add_edge(tiny_graph, 1, 2);
    add_edge(tiny_graph, 2, 0);
    
    test_graph_properties(tiny_graph, "Triangle Graph (n=3)");
    test_euler_algorithm(tiny_graph, "Triangle Graph");
    test_hamilton_algorithm(tiny_graph, "Triangle Graph");
    
    free_graph(tiny_graph);
    
    printf("\n=== Debug Complete ===\n");
    return 0;
}
