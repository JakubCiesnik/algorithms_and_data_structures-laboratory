#include "graph.h"

int main() {
    printf("=== Library Function Testing ===\n");
    
    // Test individual functions - set breakpoints here

    // Graph* graph = generate_eulerian_hamiltonian_graph(99, 0.6);
    Graph* graph = generate_eulerian_hamiltonian_graph(34, 0.8);
    // Graph* graph = generate_eulerian_hamiltonian_graph(31, 0.3);
    
    
    print_list(find_euler_cycle_simple(graph));

    print_list(find_hamilton_cycle_simple(graph));

    free_graph(graph);

    return 0;
}