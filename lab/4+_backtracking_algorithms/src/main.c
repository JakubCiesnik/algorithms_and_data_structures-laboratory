#include "graph.h"

int main() {
    printf("=== Task I: Euler and Hamilton Cycle Algorithms ===\n\n");
    
    FILE *results_file = fopen("results/task1_results.csv", "w");
    if (!results_file) {
        printf("Error: Could not create results file\n");
        return 1;
    }
    
    fprintf(results_file, "vertices,euler_sparse_time,hamilton_sparse_time,euler_dense_time,hamilton_dense_time\n");
    
    printf("Measuring execution times for 20 measurement points...\n");
    printf("Vertices\tEuler(30%%)\tHamilton(30%%)\tEuler(70%%)\tHamilton(70%%)\n");
    printf("--------\t----------\t-------------\t----------\t-------------\n");
    
    // 20 measurement points with larger graphs
    int vertices_sizes[] = {4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 25, 30, 35, 40, 50, 60, 80, 100};
    
    for (int i = 0; i < 20; i++) {
        int n = vertices_sizes[i];
        
        printf("Processing n=%d (%d/20)...\n", n, i+1);
        
        // Generate sparse graph (30% edge density)
        printf("Generating sparse graph (n=%d)...", n);
        fflush(stdout);
        Graph* sparse_graph = generate_eulerian_hamiltonian_graph(n, 0.3);
        
        // VALIDATE sparse graph
        if (!is_eulerian(sparse_graph) || !is_connected(sparse_graph)) {
            printf("\nERROR: Sparse graph (n=%d) is not properly Eulerian/Connected!\n", n);
            printf("Eulerian: %s, Connected: %s\n", 
                   is_eulerian(sparse_graph) ? "YES" : "NO",
                   is_connected(sparse_graph) ? "YES" : "NO");
            free_graph(sparse_graph);
            continue;
        }
        printf(" OK\n");
        
        // Generate dense graph (70% edge density) 
        printf("Generating dense graph (n=%d)...", n);
        fflush(stdout);
        Graph* dense_graph = generate_eulerian_hamiltonian_graph(n, 0.7);
        
        // VALIDATE dense graph
        if (!is_eulerian(dense_graph) || !is_connected(dense_graph)) {
            printf("\nERROR: Dense graph (n=%d) is not properly Eulerian/Connected!\n", n);
            printf("Eulerian: %s, Connected: %s\n", 
                   is_eulerian(dense_graph) ? "YES" : "NO",
                   is_connected(dense_graph) ? "YES" : "NO");
            free_graph(sparse_graph);
            free_graph(dense_graph);
            continue;
        }
        printf(" OK\n");
        
        // Measure Euler cycle time for sparse graph
        clock_t start = clock();
        IntList* euler_sparse = find_euler_cycle(sparse_graph);
        clock_t end = clock();
        double euler_sparse_time = get_time_diff(start, end);
        
        // Measure Hamilton cycle time for sparse graph
        start = clock();
        IntList* hamilton_sparse = find_hamilton_cycle(sparse_graph);
        end = clock();
        double hamilton_sparse_time = get_time_diff(start, end);
        
        // Measure Euler cycle time for dense graph
        start = clock();
        IntList* euler_dense = find_euler_cycle(dense_graph);
        end = clock();
        double euler_dense_time = get_time_diff(start, end);
        
        // Measure Hamilton cycle time for dense graph
        start = clock();
        IntList* hamilton_dense = find_hamilton_cycle(dense_graph);
        end = clock();
        double hamilton_dense_time = get_time_diff(start, end);
        
        // Handle timeouts (if Hamilton algorithm times out, record the timeout time)
        if (hamilton_sparse == NULL && hamilton_sparse_time < 0.001) {
            hamilton_sparse_time = 5.0; // timeout time
        }
        if (hamilton_dense == NULL && hamilton_dense_time < 0.001) {
            hamilton_dense_time = 5.0; // timeout time
        }
        
        // Print results
        printf("%d\t\t%.6f\t%.6f\t\t%.6f\t%.6f\n", 
               n, euler_sparse_time, hamilton_sparse_time, 
               euler_dense_time, hamilton_dense_time);
        
        // Write to CSV
        fprintf(results_file, "%d,%.6f,%.6f,%.6f,%.6f\n",
                n, euler_sparse_time, hamilton_sparse_time,
                euler_dense_time, hamilton_dense_time);
        fflush(results_file); // Ensure data is written immediately
        
        // Verify results - Euler cycles MUST be found for valid Eulerian graphs
        bool sparse_euler_ok = (euler_sparse != NULL);
        bool sparse_hamilton_ok = (hamilton_sparse != NULL);
        bool dense_euler_ok = (euler_dense != NULL);
        bool dense_hamilton_ok = (hamilton_dense != NULL);
        
        if (!sparse_euler_ok || !dense_euler_ok) {
            printf("CRITICAL ERROR: Failed to find Euler cycles for n=%d - This should never happen!\n", n);
            printf("Sparse Euler: %s, Dense Euler: %s\n", 
                   sparse_euler_ok ? "OK" : "FAILED",
                   dense_euler_ok ? "OK" : "FAILED");
            // Continue anyway but mark the error
        }
        if (!sparse_hamilton_ok || !dense_hamilton_ok) {
            printf("Note: Hamilton cycle search timed out or failed for n=%d (expected for larger graphs)\n", n);
        }
        
        // Cleanup
        if (euler_sparse) free_list(euler_sparse);
        if (hamilton_sparse) free_list(hamilton_sparse);
        if (euler_dense) free_list(euler_dense);
        if (hamilton_dense) free_list(hamilton_dense);
        free_graph(sparse_graph);
        free_graph(dense_graph);
    }
    
    fclose(results_file);
    printf("\nResults saved to ../results/task1_results.csv\n");
    
    printf("\n=== Algorithm Complexity Analysis ===\n");
    printf("Euler cycle problem: O(E) - Polynomial time complexity\n");
    printf("Hamilton cycle problem: O(n!) - Exponential time complexity (NP-complete)\n");
    
    printf("\n=== Observations ===\n");
    printf("1. Euler cycle algorithm should perform similarly for both sparse and dense graphs\n");
    printf("   since it depends on the number of edges, not density.\n");
    printf("2. Hamilton cycle algorithm will likely take longer for dense graphs\n");
    printf("   due to more possibilities to explore during backtracking.\n");
    printf("3. As graph size increases, Hamilton cycle time should grow exponentially\n");
    printf("   while Euler cycle time grows linearly.\n");
    
    return 0;
}
