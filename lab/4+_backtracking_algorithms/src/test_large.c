#include "graph.h"

void test_larger_graphs() {
    printf("=== Testing Larger Graphs ===\n");
    
    int test_sizes[] = {15, 20, 25};  // Start with smaller sizes
    
    for (int i = 0; i < 3; i++) {
        int n = test_sizes[i];
        printf("\n--- Testing n=%d ---\n", n);
        fflush(stdout);
        
        // Test sparse graph
        printf("Generating sparse graph...\n");
        fflush(stdout);
        Graph* sparse = generate_eulerian_hamiltonian_graph(n, 0.3);
        bool sparse_eulerian = is_eulerian(sparse);
        bool sparse_connected = is_connected(sparse);
        
        printf("Sparse (30%%): vertices=%d, edges=%d, eulerian=%s, connected=%s\n", 
               sparse->vertices, sparse->edges, 
               sparse_eulerian ? "YES" : "NO",
               sparse_connected ? "YES" : "NO");
        fflush(stdout);
        
        // Test Euler cycle
        printf("Finding Euler cycle...\n");
        fflush(stdout);
        clock_t start = clock();
        IntList* euler_sparse = find_euler_cycle(sparse);
        clock_t end = clock();
        double euler_time = get_time_diff(start, end);
        
        printf("Euler cycle found: %s (%.6f seconds)\n", 
               euler_sparse ? "YES" : "NO", euler_time);
        fflush(stdout);
        
        if (euler_sparse) free_list(euler_sparse);
        free_graph(sparse);
    }
}

int main() {
    test_larger_graphs();
    return 0;
}
