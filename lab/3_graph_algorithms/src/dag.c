#include "dag.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// Shuffle helper
static void shuffle(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
    }
}

// Generate a connected DAG
int **generate_dag(int n, double density) {
    int **mat = alloc_matrix(n);
    int *order = malloc(n * sizeof *order);
    for (int i = 0; i < n; i++) order[i] = i;
    shuffle(order, n);

    // Map label -> position for easy checks
    int *pos = malloc(n * sizeof *pos);
    for (int i = 0; i < n; i++) pos[order[i]] = i;

    // Ensure connectivity: a simple chain in topo order
    for (int i = 0; i < n - 1; i++) {
        int u = order[i], v = order[i+1];
        mat[u][v] = 1;
    }

    int max_edges = n * (n - 1) / 2;
    int target = (int)(density * max_edges);
    int added = n - 1;

    while (added < target) {
        int i = rand() % n;
        int j = rand() % n;
        int u = order[i], v = order[j];
        // Only forward edges in topo order
        if (pos[u] < pos[v] && mat[u][v] == 0) {
            mat[u][v] = 1;
            added++;
        }
    }

    free(order);
    free(pos);
    return mat;
}

// ---------- Topo sort (matrix via DFS) ----------
static void dfs_mat(int u, int **m, int n, int *vis, int *stack, int *sp) {
    vis[u] = 1;
    for (int v = 0; v < n; v++) {
        if (m[u][v] && !vis[v]) dfs_mat(v, m, n, vis, stack, sp);
    }
    stack[(*sp)++] = u;
}

void topo_sort_matrix(int **mat, int n, int *out_order) {
    int *vis = calloc(n, sizeof *vis);
    int *stack = malloc(n * sizeof *stack);
    int sp = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs_mat(i, mat, n, vis, stack, &sp);
    }
    // reverse
    for (int i = 0; i < n; i++) {
        out_order[i] = stack[n - 1 - i];
    }
    free(vis);
    free(stack);
}

// ---------- Topo sort (Kahn's, adjacency list) ----------
void topo_sort_list(AdjNode **adj, int n, int *out_order) {
    int *indeg = calloc(n, sizeof *indeg);
    for (int u = 0; u < n; u++) {
        for (AdjNode *p = adj[u]; p; p = p->next) {
            indeg[p->v]++;
        }
    }
    int *queue = malloc(n * sizeof *queue);
    int qh = 0, qt = 0;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) queue[qt++] = i;
    }
    int idx = 0;
    while (qh < qt) {
        int u = queue[qh++];
        out_order[idx++] = u;
        for (AdjNode *p = adj[u]; p; p = p->next) {
            if (--indeg[p->v] == 0) queue[qt++] = p->v;
        }
    }
    assert(idx == n);  // must remain a DAG
    free(indeg);
    free(queue);
}
