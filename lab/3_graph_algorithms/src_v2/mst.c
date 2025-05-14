// =========================
// Prim’s MST (Matrix + CSR+Heap)
// =========================
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dag.c"    // for load_matrix & CSRGraph

// — Matrix-based Prim (O(V^2)) —
int prim_matrix(int** W,int n){
    char* in_mst=calloc(n,1);
    int* key=malloc(n*sizeof(int));
    for(int i=0;i<n;i++) key[i]=INT_MAX;
    key[0]=0;
    int total=0;
    for(int iter=0;iter<n;iter++){
        int u=-1;
        for(int i=0;i<n;i++)
            if(!in_mst[i]&&(u<0||key[i]<key[u])) u=i;
        in_mst[u]=1; total+=key[u];
        for(int v=0;v<n;v++){
            if(!in_mst[v]&&W[u][v]&&W[u][v]<key[v])
                key[v]=W[u][v];
        }
    }
    free(in_mst); free(key);
    return total;
}

// — CSR+Min-Heap for Prim’s (O(E log V)) —

typedef struct {
    int* heap;    // heap of vertex IDs
    int* pos;     // pos[v] = index of v in heap[]
    int* key;     // current best key[v]
    int  size;
} MinHeap;

MinHeap* heap_create(int n){
    MinHeap* H=malloc(sizeof(*H));
    H->heap=malloc(n*sizeof(int));
    H->pos =malloc(n*sizeof(int));
    H->key =malloc(n*sizeof(int));
    H->size=0;
    return H;
}

void heap_swap(MinHeap* H,int i,int j){
    int vi=H->heap[i], vj=H->heap[j];
    H->pos[vi]=j; H->pos[vj]=i;
    int tmp=H->heap[i]; H->heap[i]=H->heap[j]; H->heap[j]=tmp;
}

void heap_sift_up(MinHeap* H,int i){
    while(i>0){
        int p=(i-1)/2;
        if(H->key[H->heap[i]]<H->key[H->heap[p]]){
            heap_swap(H,i,p);
            i=p;
        } else break;
    }
}

void heap_sift_down(MinHeap* H,int i){
    int n=H->size;
    while(1){
        int l=2*i+1, r=2*i+2, smallest=i;
        if(l<n && H->key[H->heap[l]]<H->key[H->heap[smallest]]) smallest=l;
        if(r<n && H->key[H->heap[r]]<H->key[H->heap[smallest]]) smallest=r;
        if(smallest!=i){ heap_swap(H,i,smallest); i=smallest; }
        else break;
    }
}

void heap_insert(MinHeap* H,int v,int k){
    int i=H->size++;
    H->heap[i]=v; H->pos[v]=i; H->key[v]=k;
    heap_sift_up(H,i);
}

int heap_extract_min(MinHeap* H){
    int v=H->heap[0];
    H->heap[0]=H->heap[--H->size];
    H->pos[H->heap[0]]=0;
    heap_sift_down(H,0);
    return v;
}

void heap_decrease_key(MinHeap* H,int v,int newk){
    H->key[v]=newk;
    heap_sift_up(H,H->pos[v]);
}

// Prim’s using CSRGraph; weights in parallel array Wcsr->weights
int prim_csr(CSRGraph* g,int* Wcsr){
    int n=g->n;
    char* in_mst=calloc(n,1);
    MinHeap* H=heap_create(n);

    // init heap keys
    for(int v=0;v<n;v++) heap_insert(H,v,INT_MAX);
    heap_decrease_key(H,0,0);

    int total=0;
    while(H->size){
        int u=heap_extract_min(H);
        in_mst[u]=1;
        total += H->key[u];
        for(int i=g->row_ptr[u]; i<g->row_ptr[u+1]; i++){
            int v=g->col_idx[i], w=Wcsr[i];
            if(!in_mst[v] && w < H->key[v]){
                heap_decrease_key(H,v,w);
            }
        }
    }

    free(in_mst);
    free(H->heap); free(H->pos); free(H->key); free(H);
    return total;
}

