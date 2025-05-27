#include <stdbool.h>
#include "graph.h"

// Graph functions
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->edges = 0;
    
    // Allocate adjacency matrix
    graph->adjacency_matrix = (bool**)malloc(vertices * sizeof(bool*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_matrix[i] = (bool*)calloc(vertices, sizeof(bool));
    }
    
    return graph;
}

void free_graph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->vertices; i++) {
            free(graph->adjacency_matrix[i]);
        }
        free(graph->adjacency_matrix);
        free(graph);
    }
}

void add_edge(Graph* graph, int u, int v) {
    if (u < graph->vertices && v < graph->vertices && u != v) {
        if (!graph->adjacency_matrix[u][v]) {
            graph->adjacency_matrix[u][v] = 1;
            graph->adjacency_matrix[v][u] = 1; // Undirected graph
            graph->edges++;
        }
    }
}

bool has_edge(Graph* graph, int u, int v) {
    if (u < graph->vertices && v < graph->vertices) {
        return graph->adjacency_matrix[u][v] == 1;
    }
    return false;
}

void print_graph(Graph* graph) {
    printf("Graph with %d vertices and %d edges:\n", graph->vertices, graph->edges);
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

// DFS for connectivity check
void dfs_connectivity(Graph* graph, int v, bool* visited) {
    visited[v] = true;
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacency_matrix[v][i] && !visited[i]) {
            dfs_connectivity(graph, i, visited);
        }
    }
}

bool is_connected(Graph* graph) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    
    // Find first vertex with non-zero degree
    int start = -1;
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->vertices; j++) {
            degree += graph->adjacency_matrix[i][j];
        }
        if (degree > 0) {
            start = i;
            break;
        }
    }
    
    if (start == -1) {
        free(visited);
        return false; // No edges
    }
    
    dfs_connectivity(graph, start, visited);
    
    // Check if all vertices with edges are visited
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->vertices; j++) {
            degree += graph->adjacency_matrix[i][j];
        }
        if (degree > 0 && !visited[i]) {
            free(visited);
            return false;
        }
    }
    
    free(visited);
    return true;
}

bool is_eulerian(Graph* graph) {
    if (!is_connected(graph)) return false;
    
    // Check if all vertices have even degree
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->vertices; j++) {
            degree += graph->adjacency_matrix[i][j];
        }
        if (degree % 2 != 0) {
            return false;
        }
    }
    return true;
}

// List functions
IntList* create_list(int capacity) {
    IntList* list = (IntList*)malloc(sizeof(IntList));
    list->items = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void free_list(IntList* list) {
    if (list) {
        free(list->items);
        free(list);
    }
}

void add_to_list(IntList* list, int item) {
    if (list->size < list->capacity) {
        list->items[list->size] = item;
        list->size++;
    }
}

void remove_from_list(IntList* list, int item) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i] == item) {
            for (int j = i; j < list->size - 1; j++) {
                list->items[j] = list->items[j + 1];
            }
            list->size--;
            break;
        }
    }
}

bool contains(IntList* list, int item) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i] == item) {
            return true;
        }
    }
    return false;
}

void print_list(IntList* list) {
    printf("[");
    for (int i = 0; i < list->size; i++) {
        printf("%d", list->items[i]);
        if (i < list->size - 1) printf(", ");
    }
    printf("]\n");
}

double get_time_diff(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}
