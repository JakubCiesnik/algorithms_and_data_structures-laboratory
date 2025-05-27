#include "graph.h"

#define TIMEOUT_SECONDS 1.0  // 1 second timeout
#define NUM_RUNS 3           // Multiple runs for averaging

double measure_algorithm_time(Graph* graph, bool is_euler) {
    double total_time = 0.0;
    int successful_runs = 0;
    
    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();
        IntList* result = NULL;
        
        if (is_euler) {
            result = find_euler_cycle_simple(graph);
        } else {
            result = find_hamilton_cycle_with_timeout(graph, TIMEOUT_SECONDS);
        }
        
        clock_t end = clock();
        double time_taken = get_time_diff(start, end);
        
        if (result != NULL || time_taken >= TIMEOUT_SECONDS) {
            total_time += time_taken;
            successful_runs++;
        }
        
        if (result) free_list(result);
        
        // Break early if timeout reached
        if (time_taken >= TIMEOUT_SECONDS) {
            return TIMEOUT_SECONDS; // Return timeout value
        }
    }
    
    return successful_runs > 0 ? total_time / successful_runs : TIMEOUT_SECONDS;
}

int main() {
    printf("=== Task I: Euler and Hamilton Cycle Algorithms ===\n\n");
    
    FILE *results_file = fopen("results/task1_results.csv", "w");
    if (!results_file) {
        printf("Error: Could not create results file\n");
        return 1;
    }
    
    fprintf(results_file, "vertices,euler_sparse_time,hamilton_sparse_time,euler_dense_time,hamilton_dense_time\n");
    
    printf("Measuring execution times (%.1fs timeout)...\n", TIMEOUT_SECONDS);
    printf("Vertices\tEuler(30%%)\tHamilton(30%%)\tEuler(70%%)\tHamilton(70%%)\n");
    printf("--------\t----------\t-------------\t----------\t-------------\n");
    
    // Smaller vertex sizes for more reliable results
    int vertices_sizes[] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42};
    
    for (int i = 0; i < 20; i++) {
        int n = vertices_sizes[i];
        
        // Generate sparse graph (30% edge density)
        Graph* sparse_graph = generate_eulerian_hamiltonian_graph(n, 0.3);
        
        // Generate dense graph (70% edge density)
        Graph* dense_graph = generate_eulerian_hamiltonian_graph(n, 0.7);
        
        printf("Testing %d vertices... ", n);
        fflush(stdout);
        
        // Measure times with averaging and timeout protection
        double euler_sparse_time = measure_algorithm_time(sparse_graph, true);
        double hamilton_sparse_time = measure_algorithm_time(sparse_graph, false);
        double euler_dense_time = measure_algorithm_time(dense_graph, true);
        double hamilton_dense_time = measure_algorithm_time(dense_graph, false);
        
        // Print results
        printf("Done\n");
        printf("%d\t\t%.6f\t", n, euler_sparse_time);
        if (hamilton_sparse_time >= TIMEOUT_SECONDS) {
            printf("TIMEOUT\t\t");
        } else {
            printf("%.6f\t\t", hamilton_sparse_time);
        }
        printf("%.6f\t", euler_dense_time);
        if (hamilton_dense_time >= TIMEOUT_SECONDS) {
            printf("TIMEOUT\n");
        } else {
            printf("%.6f\n", hamilton_dense_time);
        }
        
        // Save to CSV file
        fprintf(results_file, "%d,%.6f,%.6f,%.6f,%.6f\n", 
                n, euler_sparse_time, hamilton_sparse_time, euler_dense_time, hamilton_dense_time);
        
        // Clean up memory
        free_graph(sparse_graph);
        free_graph(dense_graph);
    }
    
    fclose(results_file);
    printf("\nResults saved to results/task1_results.csv\n");
    
    return 0;
}
