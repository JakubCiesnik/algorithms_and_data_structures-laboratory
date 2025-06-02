#include "graph.h"
#include <stdio.h>

// Read graph from adjacency matrix in a text file
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
        printf("%d", cycle->items[i] + 1);
        if (i < cycle->size - 1) printf(" ");
    }
    printf("\n");
}

void print_hamilton_cycle(int *cycle, int length) {
    if (!cycle || length == 0) {
        printf("No cycle found\n");
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("%d", cycle[i] + 1); 
        if (i < length - 1) printf(" ");
    }
    printf("\n");
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

    // Hamiltonian cycle from vertex 1 (index 0)
    int *ham_cycle = NULL;
    int ham_length = 0;
    if (hamiltonian_cycle(graph, 0, &ham_cycle, &ham_length)) {
        printf("Hamiltonian cycle:\n");
        print_hamilton_cycle(ham_cycle, ham_length);
        free(ham_cycle);
    } else {
        printf("Hamiltonian cycle:\nNo cycle found\n");
    }

    free_list(euler_cycle);
    free_graph(graph);

    return 0;
}
