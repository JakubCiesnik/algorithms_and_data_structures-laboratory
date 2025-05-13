#include <stdio.h>
#include <stdlib.h>

// Load an n×n adjacency matrix from text file: first line is n
int** load_matrix(const char* filename, int* out_n) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { perror("load_matrix: fopen"); exit(EXIT_FAILURE); }

    int n;
    fscanf(fp, "%d", &n);
    *out_n = n;

    int** mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    return mat;
}

// Store an n×n adjacency matrix to text file
void store_matrix(const char* filename, int** mat, int n) {
    FILE* fp = fopen(filename, "w");
    if (!fp) { perror("store_matrix: fopen"); exit(EXIT_FAILURE); }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, "%d%s", mat[i][j], (j + 1 < n) ? " " : "\n");
        }
    }
    fclose(fp);
}

// Simple linked-list node for adjacency lists
typedef struct Node {
    int        vertex;
    struct Node* next;
} Node;

// Convert adjacency matrix -> adjacency list
Node** matrix_to_list(int** mat, int n) {
    Node** list = calloc(n, sizeof(Node*));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j]) {
                Node* node = malloc(sizeof(Node));
                node->vertex = j;
                node->next   = list[i];
                list[i]      = node;
            }
        }
    }
    return list;
}

// -----------------------------------------------------------------------------
// Topological Sort: DFS-based (Adjacency Matrix)
// -----------------------------------------------------------------------------

// Helper DFS: mark visited, then push on stack
static void dfs_visit(int u, int** mat, int n, int* visited, int* stack, int* top) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (mat[u][v] && !visited[v]) {
            dfs_visit(v, mat, n, visited, stack, top);
        }
    }
    stack[(*top)++] = u;
}

// Return array of size n containing one valid topological order
int* topological_sort_matrix(int** mat, int n) {
    int* visited = calloc(n, sizeof(int));
    int* stack   = malloc(n * sizeof(int));
    int  top_idx = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_visit(i, mat, n, visited, stack, &top_idx);
        }
    }
    // Reverse stack to get correct order
    for (int i = 0; i < top_idx / 2; i++) {
        int tmp = stack[i];
        stack[i] = stack[top_idx - 1 - i];
        stack[top_idx - 1 - i] = tmp;
    }
    free(visited);
    return stack;
}

// -----------------------------------------------------------------------------
// Topological Sort: Kahn’s Algorithm (uses matrix->list internally)
// -----------------------------------------------------------------------------

int* topological_sort_list(int** mat, int n) {
    // 1) Compute in-degrees
    int* indeg = calloc(n, sizeof(int));
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (mat[u][v]) indeg[v]++;

    // 2) Enqueue all zero in-degree vertices
    int* queue = malloc(n * sizeof(int));
    int  head = 0, tail = 0;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) queue[tail++] = i;

    // 3) Process the queue
    int* order = malloc(n * sizeof(int));
    int  idx   = 0;
    while (head < tail) {
        int u = queue[head++];
        order[idx++] = u;
        for (int v = 0; v < n; v++) {
            if (mat[u][v] && --indeg[v] == 0) {
                queue[tail++] = v;
            }
        }
    }

    free(indeg);
    free(queue);
    return order;
}

