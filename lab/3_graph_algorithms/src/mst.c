#include "mst.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

// ---------- Generate weighted graph ----------
int **generate_mst_graph(int n, double density) {
    int **mat = alloc_matrix(n);
    // build a spanning tree
    for (int i = 1; i < n; i++) {
        int j = rand() % i;
        int w = rand() % 1000 + 1;
        mat[i][j] = mat[j][i] = w;
    }
    int max_edges = n * (n - 1) / 2;
    int target = (int)(density * max_edges);
    int added = n - 1;
    while (added < target) {
        int u = rand() % n, v = rand() % n;
        if (u == v || mat[u][v]) continue;
        int w = rand() % 1000 + 1;
        mat[u][v] = mat[v][u] = w;
        added++;
    }
    return mat;
}

// ---------- Prim (matrix) ----------
int64_t prim_matrix(int **mat, int n) {
    uint8_t *in_mst = calloc(n, sizeof *in_mst);
    int *min_e = malloc(n * sizeof *min_e);
    for (int i = 0; i < n; i++) min_e[i] = INT_MAX;
    min_e[0] = 0;
    int64_t total = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!in_mst[j] && (u < 0 || min_e[j] < min_e[u])) {
                u = j;
            }
        }
        in_mst[u] = 1;
        total += min_e[u];
        for (int v = 0; v < n; v++) {
            if (mat[u][v] && !in_mst[v] && mat[u][v] < min_e[v]) {
                min_e[v] = mat[u][v];
            }
        }
    }
    free(in_mst);
    free(min_e);
    return total;
}

// ---------- Simple binary min-heap ----------
typedef struct { int key, v; } HeapNode;
typedef struct {
    HeapNode *data;
    int size, cap;
} MinHeap;

static void heap_init(MinHeap *h) {
    h->data = NULL; h->size = 0; h->cap = 0;
}

static void heap_push(MinHeap *h, HeapNode x) {
    if (h->size == h->cap) {
        h->cap = h->cap ? h->cap * 2 : 64;
        h->data = realloc(h->data, h->cap * sizeof *h->data);
    }
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].key <= x.key) break;
        h->data[i] = h->data[p];
        i = p;
    }
    h->data[i] = x;
}

static HeapNode heap_pop(MinHeap *h) {
    assert(h->size > 0);
    HeapNode ret = h->data[0];
    HeapNode last = h->data[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i + 1, r = l + 1;
        if (l >= h->size) break;
        int best = (r < h->size && h->data[r].key < h->data[l].key) ? r : l;
        if (h->data[best].key >= last.key) break;
        h->data[i] = h->data[best];
        i = best;
    }
    h->data[i] = last;
    return ret;
}

static void heap_free(MinHeap *h) { free(h->data); }

// ---------- Prim (list + heap) ----------
int64_t prim_list(int **mat, int n) {
    AdjNode **adj = matrix_to_list(mat, n, 1);
    uint8_t *in_mst = calloc(n, sizeof *in_mst);
    MinHeap heap; heap_init(&heap);
    heap_push(&heap, (HeapNode){ 0, 0 });
    int64_t total = 0;
    int taken = 0;
    while (taken < n) {
        HeapNode hn = heap_pop(&heap);
        if (in_mst[hn.v]) continue;
        in_mst[hn.v] = 1;
        total += hn.key;
        taken++;
        for (AdjNode *p = adj[hn.v]; p; p = p->next) {
            if (!in_mst[p->v]) {
                heap_push(&heap, (HeapNode){ p->weight, p->v });
            }
        }
    }
    heap_free(&heap);
    free(in_mst);
    free_adjlist(adj, n);
    return total;
}
