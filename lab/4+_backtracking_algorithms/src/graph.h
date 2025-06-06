#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct {
    bool **adjacency_matrix;
    int vertices;
    int edges;
} Graph;

typedef struct {
    int *items;
    int size;
    int capacity;
} IntList;

typedef struct {
    bool *visited;
    int *path;
    int path_size;
    int used_count;
    int start_vertex;
} SearchState;

typedef struct {
    IntList **paths;
    int count;
    int capacity;
} PathList;

// Graph functions
Graph* create_graph(int vertices);
void free_graph(Graph* graph);
void add_edge(Graph* graph, int u, int v);
bool has_edge(Graph* graph, int u, int v);
void print_graph(Graph* graph);
bool is_connected(Graph* graph);
bool is_eulerian(Graph* graph);

// Graph generation functions
Graph* generate_eulerian_hamiltonian_graph(int vertices, double edge_density);
void make_hamiltonian_cycle(Graph* graph);
void add_triangles_for_density(Graph* graph, double edge_density);
bool try_add_triangle(Graph* graph, int v1, int v2, int v3);
void swap_vertices(Graph* graph, int v1, int v2);
void randomize_vertex_ordering(Graph* graph);

// List functions
IntList* create_list(int capacity);
void free_list(IntList* list);
void add_to_list(IntList* list, int item);
void remove_from_list(IntList* list, int item);
bool contains(IntList* list, int item);
void print_list(IntList* list);

// Simple Euler cycle finder (find_euler.c)
IntList* find_euler_cycle_simple(Graph* graph);
void euler(Graph* graph, int v, bool **visited_edges);

// Simple Hamilton cycle finder (find_hamilton.c)
IntList* find_hamilton_cycle_simple(Graph* graph);
IntList* find_hamilton_cycle_with_timeout(Graph* graph, double timeout_sec);
bool hamiltonian_cycle(Graph *graph, int start_vertex, int **cycle, int *cycle_length);
SearchState* init_search_state(int vertices, int start_vertex);
void free_search_state(SearchState *state);
PathList* find_all_hamiltonian_paths(Graph *graph, int start_vertex);

// Timing functions
double get_time_diff(clock_t start, clock_t end);

#endif
