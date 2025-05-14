// =========================
// Topological Sort + CSR
// =========================
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// — Matrix I/O —

int** load_matrix(const char* fname, int* out_n) {
    FILE* f = fopen(fname, "r"); if(!f){ perror("load"); exit(1); }
    int n; fscanf(f, "%d", &n);
    *out_n = n;
    int** M = malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        M[i]=malloc(n*sizeof(int));
        for(int j=0;j<n;j++) fscanf(f, "%d", &M[i][j]);
    }
    fclose(f);
    return M;
}

void store_matrix(const char* fname, int** M, int n){
    FILE* f = fopen(fname, "w"); if(!f){ perror("store"); exit(1); }
    fprintf(f, "%d\n", n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fprintf(f, "%d%c", M[i][j], j+1<n?' ':'\n');
        }
    }
    fclose(f);
}

// — CSR Representation —

typedef struct {
    int n;        // number of vertices
    int E;        // number of edges
    int* row_ptr; // size n+1
    int* col_idx; // size E
} CSRGraph;

// Build CSR from adjacency matrix
CSRGraph* matrix_to_csr(int** M, int n){
    int count=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(M[i][j]) count++;
    CSRGraph* g = malloc(sizeof(*g));
    g->n = n; g->E = count;
    g->row_ptr = malloc((n+1)*sizeof(int));
    g->col_idx = malloc(count*sizeof(int));
    int idx=0;
    for(int i=0;i<n;i++){
        g->row_ptr[i]=idx;
        for(int j=0;j<n;j++){
            if(M[i][j]) g->col_idx[idx++]=j;
        }
    }
    g->row_ptr[n]=idx;
    return g;
}

void free_csr(CSRGraph* g){
    free(g->row_ptr);
    free(g->col_idx);
    free(g);
}

// — Topo Sort: Matrix (DFS) —

static void dfs(int u,int** M,int n,int* vis,int* st,int* t){
    vis[u]=1;
    for(int v=0;v<n;v++) if(M[u][v] && !vis[v]) dfs(v,M,n,vis,st,t);
    st[(*t)++]=u;
}
int* topo_matrix(int** M,int n){
    int* vis=calloc(n,sizeof(int));
    int* st =malloc(n*sizeof(int)); int t=0;
    for(int i=0;i<n;i++) if(!vis[i]) dfs(i,M,n,vis,st,&t);
    // reverse
    for(int i=0;i<n/2;i++){
        int tmp=st[i]; st[i]=st[n-1-i]; st[n-1-i]=tmp;
    }
    free(vis);
    return st;
}

// — Topo Sort: CSR (Kahn) —

void topo_csr(CSRGraph* g,int* out_order){
    int n=g->n;
    int* indeg=calloc(n,sizeof(int));
    // compute in-deg
    for(int u=0;u<n;u++){
        for(int i=g->row_ptr[u];i<g->row_ptr[u+1];i++){
            indeg[g->col_idx[i]]++;
        }
    }
    int* q=malloc(n*sizeof(int)), front=0, back=0;
    for(int i=0;i<n;i++) if(indeg[i]==0) q[back++]=i;
    int idx=0;
    while(front<back){
        int u=q[front++]; out_order[idx++]=u;
        for(int i=g->row_ptr[u];i<g->row_ptr[u+1];i++){
            int v=g->col_idx[i];
            if(--indeg[v]==0) q[back++]=v;
        }
    }
    free(indeg); free(q);
}

