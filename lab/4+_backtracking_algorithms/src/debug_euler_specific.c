#include "graph.h"

void debug_euler_generation() {
    printf("=== Debugging Euler Graph Generation ===\n");
    
    for (int n = 4; n <= 10; n++) {
        printf("\n--- Testing n=%d ---\n", n);
        
        Graph* graph = generate_eulerian_hamiltonian_graph(n, 0.3);
        
        printf("Vertices: %d, Edges: %d\n", graph->vertices, graph->edges);
        
        // Check degree sequence
        printf("Degree sequence: ");
        bool all_even = true;
        for (int i = 0; i < graph->vertices; i++) {
            int degree = 0;
            for (int j = 0; j < graph->vertices; j++) {
                degree += graph->adjacency_matrix[i][j];
            }
            printf("%d ", degree);
            if (degree % 2 != 0) {
                all_even = false;
            }
        }
        printf("\n");
        
        printf("All degrees even: %s\n", all_even ? "YES" : "NO");
        printf("is_eulerian(): %s\n", is_eulerian(graph) ? "YES" : "NO");
        printf("is_connected(): %s\n", is_connected(graph) ? "YES" : "NO");
        
        // Try to find Euler cycle
        IntList* euler = find_euler_cycle(graph);
        printf("Euler cycle found: %s\n", euler ? "YES" : "NO");
        
        if (euler) {
            free_list(euler);
        }
        free_graph(graph);
    }
}

int main() {
    debug_euler_generation();
    return 0;
}
