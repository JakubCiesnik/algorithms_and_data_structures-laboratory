#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "undirected_graph_generator.h"
#include "prim_mst.h"

// --- CONFIGURATION FOR SMALL AND LARGE GRAPHS ---
// Uncomment one of the following blocks as needed:

// For small graphs (to see crossover for small n):
#define NUM_POINTS 20
#define START_N 1000
#define STEP_N 1000

// For large graphs (default):
// #define NUM_POINTS 15
// #define START_N 1000
// #define STEP_N 1000

float saturations_mst[] = {0.3f, 0.7f};
int num_saturations = sizeof(saturations_mst) / sizeof(saturations_mst[0]);

#define MIN_WEIGHT 1
#define MAX_WEIGHT 1000
#define NUM_RUNS_MST 3 // Number of runs for averaging

int main() {
    srand(time(NULL));
    
    for (int s_idx = 0; s_idx < num_saturations; ++s_idx) {
        float current_saturation = saturations_mst[s_idx];
        char filename[100];
        sprintf(filename, "results/prim_benchmark_sat_%.0f.csv", current_saturation * 100);
        
        FILE* results_file = fopen(filename, "w");
        if (!results_file) {
            perror("Failed to open results file");
            continue;
        }
        fprintf(results_file, "NumNodes,Saturation,TimeMatrix_ms,TimeListHeap_ms,MST_Edges_Matrix,MST_Edges_ListHeap\n");

        printf("\nRunning Prim's MST Benchmark (Saturation: %.2f)...\n", current_saturation);
        printf("%-10s | %-15s | %-18s | %-10s | %-10s\n", "Nodes", "Matrix (ms)", "ListHeap (ms)", "Edges(M)", "Edges(L)");
        printf("-----------|-----------------|--------------------|------------|------------\n");

        for (int i = 0; i < NUM_POINTS; i++) {
            int n = START_N + i * STEP_N;

            double total_time_matrix = 0;
            double total_time_list = 0;
            int total_edges_matrix = 0;
            int total_edges_list = 0;
            int successful_runs_matrix = 0;
            int successful_runs_list = 0;

            for(int run = 0; run < NUM_RUNS_MST; ++run) {
                Graph* graph = generate_random_undirected_graph(n, current_saturation, MIN_WEIGHT, MAX_WEIGHT);
                if (!graph) {
                    fprintf(stderr, "Failed to generate graph for n=%d, sat=%.2f\n", n, current_saturation);
                    continue;
                }

                int mst_edges_matrix = 0;
                int mst_edges_list = 0;
                MSTEdge* mst_res_matrix = NULL;
                MSTEdge* mst_res_list = NULL;

                // Benchmark Matrix
                clock_t start_matrix = clock();
                mst_res_matrix = prim_mst_matrix(graph, &mst_edges_matrix);
                clock_t end_matrix = clock();
                if(mst_res_matrix || n <= 1) {
                    total_time_matrix += ((double)(end_matrix - start_matrix) / CLOCKS_PER_SEC) * 1000.0;
                    total_edges_matrix += mst_edges_matrix;
                    successful_runs_matrix++;
                }
                free(mst_res_matrix);

                // Benchmark List with Heap
                clock_t start_list = clock();
                mst_res_list = prim_mst_list_heap(graph, &mst_edges_list);
                clock_t end_list = clock();
                if(mst_res_list || n <= 1) {
                    total_time_list += ((double)(end_list - start_list) / CLOCKS_PER_SEC) * 1000.0;
                    total_edges_list += mst_edges_list;
                    successful_runs_list++;
                }
                free(mst_res_list);
                free_graph(graph);
            }
            
            double avg_time_matrix = successful_runs_matrix > 0 ? total_time_matrix / successful_runs_matrix : -1.0;
            double avg_time_list = successful_runs_list > 0 ? total_time_list / successful_runs_list : -1.0;
            int avg_edges_matrix = successful_runs_matrix > 0 ? total_edges_matrix / successful_runs_matrix : -1;
            int avg_edges_list = successful_runs_list > 0 ? total_edges_list / successful_runs_list : -1;

            printf("%-10d | %-15.4f | %-18.4f | %-10d | %-10d\n", n, avg_time_matrix, avg_time_list, avg_edges_matrix, avg_edges_list);
            fprintf(results_file, "%d,%.2f,%.4f,%.4f,%d,%d\n", n, current_saturation, avg_time_matrix, avg_time_list, avg_edges_matrix, avg_edges_list);
        }
        fclose(results_file);
        printf("Benchmark for saturation %.2f finished. Results saved to %s\n", current_saturation, filename);
    }
    return 0;
}