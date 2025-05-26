#include "graph.h"

int main() {
    printf("=== Task I: Euler and Hamilton Cycle Algorithms ===\n\n");
    
    FILE *results_file = fopen("results/task1_results.csv", "w");
    if (!results_file) {
        printf("Error: Could not create results file\n");
        return 1;
    }
    
    fprintf(results_file, "vertices,euler_sparse_time,hamilton_sparse_time,euler_dense_time,hamilton_dense_time\n");
    
    printf("Measuring execution times for 15 measurement points...\n");
    printf("Vertices\tEuler(30%%)\tHamilton(30%%)\tEuler(70%%)\tHamilton(70%%)\n");
    printf("--------\t----------\t-------------\t----------\t-------------\n");
    
    // 15 measurement points
    int vertices_sizes[] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60};
    
    for (int i = 0; i < 15; i++) {
        int n = vertices_sizes[i];
        
        // Generate sparse graph (30% edge density)
        Graph* sparse_graph = generate_eulerian_hamiltonian_graph(n, 0.3);
        
        // Generate dense graph (70% edge density)
        Graph* dense_graph = generate_eulerian_hamiltonian_graph(n, 0.7);
        
        print_graph(sparse_graph);
        print_graph(dense_graph);

        // Measure Euler cycle time for sparse graph
        clock_t start = clock();
        IntList* euler_sparse = find_euler_cycle_simple(sparse_graph);
        clock_t end = clock();
        double euler_sparse_time = get_time_diff(start, end);
        
        // Measure Hamilton cycle time for sparse graph
        start = clock();
        IntList* hamilton_sparse = find_hamilton_cycle_simple(sparse_graph);
        end = clock();
        double hamilton_sparse_time = get_time_diff(start, end);
        
        // Measure Euler cycle time for dense graph
        start = clock();
        IntList* euler_dense = find_euler_cycle_simple(dense_graph);
        end = clock();
        double euler_dense_time = get_time_diff(start, end);
        
        // Measure Hamilton cycle time for dense graph
        start = clock();
        IntList* hamilton_dense = find_hamilton_cycle_simple(dense_graph);
        end = clock();
        double hamilton_dense_time = get_time_diff(start, end);
        
        // Print results
        printf("%d\t\t%.6f\t%.6f\t\t%.6f\t%.6f\n", 
               n, euler_sparse_time, hamilton_sparse_time, euler_dense_time, hamilton_dense_time);
        
        // Save to CSV file
        fprintf(results_file, "%d,%.6f,%.6f,%.6f,%.6f\n", 
                n, euler_sparse_time, hamilton_sparse_time, euler_dense_time, hamilton_dense_time);
        
        // Clean up memory
        if (euler_sparse) free_list(euler_sparse);
        if (hamilton_sparse) free_list(hamilton_sparse);
        if (euler_dense) free_list(euler_dense);
        if (hamilton_dense) free_list(hamilton_dense);
        free_graph(sparse_graph);
        free_graph(dense_graph);
    }
    
    fclose(results_file);
    printf("\nResults saved to results/task1_results.csv\n");
    
    return 0;
}
