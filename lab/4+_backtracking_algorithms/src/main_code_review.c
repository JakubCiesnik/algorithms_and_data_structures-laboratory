// #include "graph.h"
// #include <stdio.h>
//
// // Read graph from adjacency matrix in a text file
// Graph* load_graph_from_file(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (!file) {
//         perror("Cannot open input file");
//         return NULL;
//     }
//
//     int matrix[100][100]; // max 100x100 matrix
//     int n = 0;
//
//     char line[1024];
//     while (fgets(line, sizeof(line), file)) {
//         if (line[0] == '-' || line[0] == '\n') continue;
//
//         int col = 0;
//         char *token = strtok(line, " \t\r\n");
//         while (token) {
//             matrix[n][col++] = atoi(token);
//             token = strtok(NULL, " \t\r\n");
//         }
//         n++;
//     }
//
//     fclose(file);
//
//     Graph *graph = create_graph(n);
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             if (matrix[i][j]) {
//                 add_edge(graph, i, j);
//             }
//         }
//     }
//
//     return graph;
// }
//
// void print_cycle(IntList *cycle) {
//     if (!cycle) {
//         printf("No cycle found\n");
//         return;
//     }
//     for (int i = 0; i < cycle->size; i++) {
//         printf("%d", cycle->items[i] + 1);
//         if (i < cycle->size - 1) printf(" ");
//     }
//     printf("\n");
// }
//
// void print_hamilton_cycle(int *cycle, int length) {
//     if (!cycle || length == 0) {
//         printf("No cycle found\n");
//         return;
//     }
//     for (int i = 0; i < length; i++) {
//         printf("%d", cycle[i] + 1); 
//         if (i < length - 1) printf(" ");
//     }
//     printf("\n");
// }
//
// int main() {
//     const char *filename = "dataset/euler.txt";
//     Graph *graph = load_graph_from_file(filename);
//
//     if (!graph) {
//         fprintf(stderr, "Error loading graph from file.\n");
//         return 1;
//     }
//
//     printf("=== Euler and Hamilton Cycles ===\n\n");
//
//     // Euler cycle
//     IntList *euler_cycle = find_euler_cycle_simple(graph);
//     printf("Euler cycle:\n");
//     print_cycle(euler_cycle);
//     printf("\n");
//
//     // Hamiltonian cycle from vertex 1 (index 0)
//     int *ham_cycle = NULL;
//     int ham_length = 0;
//     if (hamiltonian_cycle(graph, 0, &ham_cycle, &ham_length)) {
//         printf("Hamiltonian cycle:\n");
//         print_hamilton_cycle(ham_cycle, ham_length);
//         free(ham_cycle);
//     } else {
//         printf("Hamiltonian cycle:\nNo cycle found\n");
//     }
//
//     free_list(euler_cycle);
//     free_graph(graph);
//
//     return 0;
// }
//
//
//
#include "graph.h"
#include <stdio.h>

Graph* load_graph_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open input file");
        return NULL;
    }

    int matrix[100][100]; // max 100x100 matrix
    int n = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '-' || line[0] == '\n') continue;

        int col = 0;
        char *token = strtok(line, " \t\r\n");
        while (token) {
            matrix[n][col++] = atoi(token);
            token = strtok(NULL, " \t\r\n");
        }
        n++;
    }

    fclose(file);

    Graph *graph = create_graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j]) {
                add_edge(graph, i, j);
            }
        }
    }

    return graph;
}

void print_cycle(IntList *cycle) {
    if (!cycle) {
        printf("No cycle found\n");
        return;
    }
    for (int i = 0; i < cycle->size; i++) {
        printf("%d", cycle->items[i] + 1); // Convert to 1-based index
        if (i < cycle->size - 1) printf(" ");
    }
    printf("\n");
}

void print_all_hamiltonian_cycles(Graph *graph, int start_vertex) {
    PathList *all_paths = find_all_hamiltonian_paths(graph, start_vertex);
    int count = 0;

    printf("Hamiltonian cycles:\n");

    for (int i = 0; i < all_paths->count; i++) {
        IntList *path = all_paths->paths[i];

        // Check if it forms a cycle (ends at start vertex)
        if (has_edge(graph, path->items[path->size - 1], start_vertex)) {
            count++;
            for (int j = 0; j < path->size; j++) {
                printf("%d ", path->items[j] + 1);
            }
            printf("%d\n", start_vertex + 1); // Close the cycle
        }
    }

    if (count == 0) {
        printf("No Hamiltonian cycles found.\n");
    }

    // Free memory
    for (int i = 0; i < all_paths->count; i++) {
        free_list(all_paths->paths[i]);
    }
    free(all_paths->paths);
    free(all_paths);
}

int main() {
    const char *filename = "dataset/euler.txt";
    Graph *graph = load_graph_from_file(filename);

    if (!graph) {
        fprintf(stderr, "Error loading graph from file.\n");
        return 1;
    }

    printf("=== Euler and Hamilton Cycles ===\n\n");

    // Euler cycle
    IntList *euler_cycle = find_euler_cycle_simple(graph);
    printf("Euler cycle:\n");
    print_cycle(euler_cycle);
    printf("\n");

    // All Hamiltonian cycles from vertex 1 (index 0)
    print_all_hamiltonian_cycles(graph, 0);

    free_list(euler_cycle);
    free_graph(graph);

    return 0;
}
