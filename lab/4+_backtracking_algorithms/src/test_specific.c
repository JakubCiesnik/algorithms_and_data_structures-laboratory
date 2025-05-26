#include "graph.h"

void test_specific_case() {
    printf("=== Testing Dense Graph Generation for n=8 ===\n");
    
    for (int attempt = 0; attempt < 5; attempt++) {
        printf("\nAttempt %d:\n", attempt + 1);
        
        Graph* graph = generate_eulerian_hamiltonian_graph(8, 0.7);
        
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
        
        IntList* euler = find_euler_cycle(graph);
        printf("Euler cycle found: %s\n", euler ? "YES" : "NO");
        
        if (euler) free_list(euler);
        free_graph(graph);
        
        // If successful, break
        if (all_even) {
            printf("SUCCESS!\n");
            break;
        }
    }
}

int main() {
    test_specific_case();
    return 0;
}
