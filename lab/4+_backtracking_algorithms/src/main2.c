// task2_benchmark.c
#include "graph.h"
#include <time.h>

#define TIMEOUT_SECONDS 300.0  // 5 minutes timeout for path enumeration
#define NUM_RUNS 3

double measure_paths_time(Graph* graph) {
    double total_time = 0.0;
    int successful_runs = 0;
    
    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();
        PathList* results = find_all_hamiltonian_paths(graph, 0);
        clock_t end = clock();
        
        double time_taken = get_time_diff(start, end);
        
        if (results != NULL) {
            total_time += time_taken;
            successful_runs++;
            
            // Cleanup paths
            for (int i = 0; i < results->count; i++) {
                free_list(results->paths[i]);
            }
            free(results->paths);
            free(results);
        }
        
        if (time_taken >= TIMEOUT_SECONDS) {
            return TIMEOUT_SECONDS;
        }
    }
    
    return successful_runs > 0 ? total_time / successful_runs : TIMEOUT_SECONDS;
}

int main() {
    printf("=== Task II: Hamiltonian Paths Benchmark ===\n\n");
    
    FILE *results_file = fopen("results/task2_results.csv", "w");
    if (!results_file) {
        printf("Error: Could not create results file\n");
        return 1;
    }
    
    fprintf(results_file, "vertices,density,time_taken,num_paths,time_per_path\n");
    
    printf("Measuring execution times (%.1fs timeout)...\n", TIMEOUT_SECONDS);
    printf("Vertices\tDensity\tTime (s)\tPaths Found\tTime/Path (ms)\n");
    printf("--------\t------\t--------\t-----------\t-------------\n");
    
    int vertices_sizes[] = {4, 6, 8, 10, 12, 14, 16};  // Smaller sizes for paths
   
    int num_sizes = sizeof(vertices_sizes)/sizeof(vertices_sizes[0]);
    for (int i = 0; i < num_sizes; i++) {      int n = vertices_sizes[i];
        
        for (float density = 0.3; density <= 0.7; density += 0.2) {
            Graph* graph = generate_eulerian_hamiltonian_graph(n, density);
            printf("Testing %d vertices (%.0f%%)... ", n, density*100);
            fflush(stdout);
            
            clock_t start = clock();
            PathList* results = find_all_hamiltonian_paths(graph, 0);
            double time_taken = get_time_diff(start, clock());
            int num_paths = results ? results->count : 0;
            
            // Print results
            printf("%.3fs\t%d\t\t%.3f\n", 
                  time_taken, 
                  num_paths,
                  num_paths > 0 ? (time_taken*1000)/num_paths : 0);
            
            // Save to CSV
            fprintf(results_file, "%d,%.2f,%.6f,%d,%.6f\n",
                    n, density, time_taken, num_paths,
                    num_paths > 0 ? (time_taken*1000)/num_paths : 0);
            
            // Cleanup
            if (results) {
                for (int p = 0; p < results->count; p++) {
                    free_list(results->paths[p]);
                }
                free(results->paths);
                free(results);
            }
            free_graph(graph);
        }
    }
    
    fclose(results_file);
    printf("\nResults saved to results/task2_results.csv\n");
    return 0;
}
