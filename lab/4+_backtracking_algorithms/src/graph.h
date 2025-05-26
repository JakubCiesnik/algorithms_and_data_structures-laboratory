#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct {
    int **adjacency_matrix;
    int vertices;
    int edges;
} Graph;

typedef struct {
    int *items;
    int size;
    int capacity;
} IntList;

// Graph functions
Graph* create_graph(int vertices);
void free_graph(Graph* graph);
void add_edge(Graph* graph, int u, int v);
bool has_edge(Graph* graph, int u, int v);
void print_graph(Graph* graph);
bool is_connected(Graph* graph);
bool is_eulerian(Graph* graph);
bool is_hamiltonian_naive(Graph* graph);

// Graph generation functions
Graph* generate_eulerian_hamiltonian_graph(int vertices, double edge_density);
void make_hamiltonian_cycle(Graph* graph);
void add_random_edges_for_euler(Graph* graph, double target_density);
void ensure_eulerian_property(Graph* graph);
void force_eulerian_property(Graph* graph);
Graph* create_simple_eulerian_hamiltonian_graph(int vertices, double edge_density);

// List functions
IntList* create_list(int capacity);
void free_list(IntList* list);
void add_to_list(IntList* list, int item);
void remove_from_list(IntList* list, int item);
bool contains(IntList* list, int item);
void print_list(IntList* list);

// Algorithm functions
IntList* find_euler_cycle(Graph* graph);
IntList* find_hamilton_cycle(Graph* graph);

// Helper functions for algorithms
void euler_recursive(Graph* graph, int v, bool **visited_edges, IntList* cycle);
void hamilton_recursive_v2(Graph* graph, int v, int start, bool* visited);

// Timing functions
double get_time_diff(clock_t start, clock_t end);

#endif
