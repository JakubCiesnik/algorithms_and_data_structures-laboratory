#include "prim_mst.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"

// Simple min-heap for (vertex, key) pairs
typedef struct {
    int vertex;
    int key;
} HeapNode;

typedef struct {
    HeapNode* data;
    int* pos; // position of vertex in heap
    int size;
    int capacity;
} MinHeap;

static MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(HeapNode));
    heap->pos = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void swap_heap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

static void min_heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    if (left < heap->size && heap->data[left].key < heap->data[smallest].key)
        smallest = left;
    if (right < heap->size && heap->data[right].key < heap->data[smallest].key)
        smallest = right;
    if (smallest != idx) {
        // Update positions
        heap->pos[heap->data[smallest].vertex] = idx;
        heap->pos[heap->data[idx].vertex] = smallest;
        swap_heap_nodes(&heap->data[smallest], &heap->data[idx]);
        min_heapify(heap, smallest);
    }
}

static HeapNode extract_min(MinHeap* heap) {
    HeapNode root = heap->data[0];
    HeapNode last = heap->data[heap->size - 1];
    heap->data[0] = last;
    heap->pos[last.vertex] = 0;
    heap->size--;
    min_heapify(heap, 0);
    return root;
}

static void decrease_key(MinHeap* heap, int v, int key) {
    int i = heap->pos[v];
    heap->data[i].key = key;
    while (i && heap->data[i].key < heap->data[(i-1)/2].key) {
        heap->pos[heap->data[i].vertex] = (i-1)/2;
        heap->pos[heap->data[(i-1)/2].vertex] = i;
        swap_heap_nodes(&heap->data[i], &heap->data[(i-1)/2]);
        i = (i-1)/2;
    }
}

static bool is_in_heap(MinHeap* heap, int v) {
    return heap->pos[v] < heap->size;
}

static void free_min_heap(MinHeap* heap) {
    free(heap->data);
    free(heap->pos);
    free(heap);
}

// Prim's MST using adjacency list and min-heap (priority queue)
MSTEdge* prim_mst_list_heap(Graph* graph, int* mst_edge_count) {
    int n = graph->num_nodes;
    int* key = malloc(n * sizeof(int));
    int* parent = malloc(n * sizeof(int));
    bool* in_mst = calloc(n, sizeof(bool));
    MinHeap* heap = create_min_heap(n);

    for (int v = 0; v < n; v++) {
        key[v] = INT_MAX;
        parent[v] = -1;
        heap->data[v].vertex = v;
        heap->data[v].key = key[v];
        heap->pos[v] = v;
    }
    key[0] = 0;
    heap->data[0].key = 0;
    heap->size = n;

    MSTEdge* mst = malloc((n-1) * sizeof(MSTEdge));
    *mst_edge_count = 0;

    while (heap->size > 0) {
        HeapNode min_node = extract_min(heap);
        int u = min_node.vertex;
        in_mst[u] = true;

        if (parent[u] != -1) {
            mst[*mst_edge_count].u = parent[u];
            mst[*mst_edge_count].v = u;
            mst[*mst_edge_count].weight = key[u];
            (*mst_edge_count)++;
        }

        AdjListNode* node = graph->adj_list_array[u];
        while (node) {
            int v = node->dest;
            int weight = node->weight;
            // Only decrease key if v is still in the heap (not yet in MST)
            if (!in_mst[v] && is_in_heap(heap, v) && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                decrease_key(heap, v, key[v]);
            }
            node = node->next;
        }
    }

    free(key);
    free(parent);
    free(in_mst);
    free_min_heap(heap);
    return mst;
}