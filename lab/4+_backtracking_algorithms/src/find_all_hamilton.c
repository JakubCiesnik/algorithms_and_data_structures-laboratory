#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Structure to store all Hamilton cycles
typedef struct {
    int **cycles;       // Array of cycles (each cycle is array of vertices)
    int *cycle_lengths; // Length of each cycle
    int count;          // Number of cycles found
    int capacity;       // Capacity of cycles array
} AllHamiltonCycles;

// Global variables for the search
static AllHamiltonCycles* all_cycles;
static bool* visited;
static int* current_path;
static int path_length;
static int start_vertex;
static clock_t search_start_time;
static double timeout_duration;

// Initialize AllHamiltonCycles structure
AllHamiltonCycles* create_all_hamilton_cycles(int initial_capacity) {
    AllHamiltonCycles* ahc = malloc(sizeof(AllHamiltonCycles));
    ahc->cycles = malloc(initial_capacity * sizeof(int*));
    ahc->cycle_lengths = malloc(initial_capacity * sizeof(int));
    ahc->count = 0;
    ahc->capacity = initial_capacity;
    return ahc;
}

// Add a cycle to the collection
void add_hamilton_cycle(AllHamiltonCycles* ahc, int* path, int length) {
    // Resize if necessary
    if (ahc->count >= ahc->capacity) {
        ahc->capacity *= 2;
        ahc->cycles = realloc(ahc->cycles, ahc->capacity * sizeof(int*));
        ahc->cycle_lengths = realloc(ahc->cycle_lengths, ahc->capacity * sizeof(int));
    }
    
    // Allocate and copy the cycle
    ahc->cycles[ahc->count] = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        ahc->cycles[ahc->count][i] = path[i];
    }
    ahc->cycle_lengths[ahc->count] = length;
    ahc->count++;
}

// Free AllHamiltonCycles structure
void free_all_hamilton_cycles(AllHamiltonCycles* ahc) {
    if (ahc) {
        for (int i = 0; i < ahc->count; i++) {
            free(ahc->cycles[i]);
        }
        free(ahc->cycles);
        free(ahc->cycle_lengths);
        free(ahc);
    }
}

// Print all Hamilton cycles
void print_all_hamilton_cycles(AllHamiltonCycles* ahc) {
    if (!ahc || ahc->count == 0) {
        printf("  No Hamilton cycles found.\n");
        return;
    }
    
    printf("Found %d Hamilton cycle(s):\n", ahc->count);
    for (int i = 0; i < ahc->count; i++) {
        printf("  Cycle %d: ", i + 1);
        for (int j = 0; j < ahc->cycle_lengths[i]; j++) {
            printf("%d", ahc->cycles[i][j]);
            if (j < ahc->cycle_lengths[i] - 1) printf(" -> ");
        }
        printf("\n");
    }
}

// Recursive function to find all Hamilton cycles
void find_all_hamilton_cycles_recursive(Graph* graph, int current_vertex) {
    // Check timeout
    clock_t current_time = clock();
    double elapsed = ((double)(current_time - search_start_time)) / CLOCKS_PER_SEC;
    if (elapsed >= timeout_duration) {
        return; // Timeout reached
    }
    
    // Add current vertex to path
    current_path[path_length] = current_vertex;
    visited[current_vertex] = true;
    path_length++;
    
    // If we've visited all vertices, check if we can return to start
    if (path_length == graph->vertices) {
        if (has_edge(graph, current_vertex, start_vertex)) {
            // Found a Hamilton cycle, add return to start
            current_path[path_length] = start_vertex;
            add_hamilton_cycle(all_cycles, current_path, path_length + 1);
        }
    } else {
        // Continue exploring unvisited vertices
        for (int next_vertex = 0; next_vertex < graph->vertices; next_vertex++) {
            if (!visited[next_vertex] && has_edge(graph, current_vertex, next_vertex)) {
                find_all_hamilton_cycles_recursive(graph, next_vertex);
            }
        }
    }
    
    // Backtrack
    path_length--;
    visited[current_vertex] = false;
}

// Main function to find all Hamilton cycles in a graph
AllHamiltonCycles* find_all_hamilton_cycles_in_graph(Graph* graph, double timeout_sec) {
    if (!graph || graph->vertices <= 0) return NULL;
    
    // Initialize global variables
    all_cycles = create_all_hamilton_cycles(10);
    visited = calloc(graph->vertices, sizeof(bool));
    current_path = malloc((graph->vertices + 1) * sizeof(int));
    path_length = 0;
    start_vertex = 0; // Start from vertex 0
    search_start_time = clock();
    timeout_duration = timeout_sec;
    
    // Start recursive search
    find_all_hamilton_cycles_recursive(graph, start_vertex);
    
    // Clean up temporary structures
    free(visited);
    free(current_path);
    
    // Return results
    AllHamiltonCycles* result = all_cycles;
    all_cycles = NULL; // Reset global variable
    return result;
}

// Test function for different graph sizes
void test_hamilton_cycles_for_sizes(int* sizes, int num_sizes, double density, double timeout_sec) {
    printf("=== Testing Hamilton Cycles for Different Graph Sizes ===\n");
    printf("Density: %.1f%%, Timeout: %.1f seconds\n\n", density * 100, timeout_sec);
    
    // Open CSV file for writing
    FILE* csv_file = fopen("../results/task2_results.csv", "w");
    if (!csv_file) {
        printf("Error: Could not create CSV file\n");
        return;
    }
    
    // Write CSV header
    fprintf(csv_file, "vertices,density,cycles_found,execution_time_seconds,timeout_occurred\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        printf("Testing graph with %d vertices...\n", n);
        
        // Generate Hamilton graph with specified density
        Graph* graph = generate_eulerian_hamiltonian_graph(n, density);
        
        clock_t start_time = clock();
        AllHamiltonCycles* cycles = find_all_hamilton_cycles_in_graph(graph, timeout_sec);
        clock_t end_time = clock();
        
        double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        bool timeout_occurred = (execution_time >= timeout_sec);
        
        if (cycles) {
            printf("  Found %d Hamilton cycles in %.6f seconds", cycles->count, execution_time);
            if (timeout_occurred) {
                printf(" (TIMEOUT)");
            }
            printf("\n");
            
            // Write to CSV
            fprintf(csv_file, "%d,%.1f,%d,%.6f,%s\n", 
                    n, density, cycles->count, execution_time, 
                    timeout_occurred ? "true" : "false");
            
            // Print graph adjacency matrix for small graphs
            if (n <= 6) {
                printf("  Graph adjacency matrix:\n");
                for (int i = 0; i < n; i++) {
                    printf("    ");
                    for (int j = 0; j < n; j++) {
                        printf("%d ", graph->adjacency_matrix[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
            
            // Print cycles for small graphs only
            if (n <= 8) {
                print_all_hamilton_cycles(cycles);
            } else if (cycles->count > 0) {
                printf("  (Cycles not printed - graph too large)\n");
            }
            
            free_all_hamilton_cycles(cycles);
        } else {
            printf("  No cycles found or timeout occurred (%.6f seconds)\n", execution_time);
            
            // Write to CSV
            fprintf(csv_file, "%d,%.1f,0,%.6f,%s\n", 
                    n, density, execution_time, 
                    timeout_occurred ? "true" : "false");
        }
        
        free_graph(graph);
        printf("\n");
    }
    
    fclose(csv_file);
    printf("Results saved to results/task2_results.csv\n");
}

// Main function for testing
int main() {
    printf("=== Hamilton Cycle Finder - All Cycles ===\n\n");
    
    // Create results directory if it doesn't exist
    (void)system("mkdir -p results");
    
    // Test with different graph sizes (reduced for practical execution)
    int test_sizes[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
    
    // Test with 50% density as specified in the requirements
    double density = 0.5;
    double timeout = 120.0; // 2 second timeout for practical results
    
    test_hamilton_cycles_for_sizes(test_sizes, num_sizes, density, timeout);
    
    printf("=== Testing Complete ===\n");
    return 0;
}
