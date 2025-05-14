// =========================
// Benchmark Runner
// =========================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int**       load_matrix(const char*, int*);
extern void        free_csr(CSRGraph*);
extern CSRGraph*   matrix_to_csr(int**, int);
extern int*        topo_matrix(int**, int);
extern void        topo_csr(CSRGraph*, int*);
extern int         prim_matrix(int**, int);
extern int         prim_csr(CSRGraph*, int*);

// measure avg ms over 10 runs
static double measure(void (*f)(int**,int), int** M, int n){
    struct timespec a,b;
    double sum=0;
    for(int i=0;i<10;i++){
        clock_gettime(CLOCK_MONOTONIC,&a);
        f(M,n);
        clock_gettime(CLOCK_MONOTONIC,&b);
        sum += (b.tv_sec-a.tv_sec)*1e3 + (b.tv_nsec-a.tv_nsec)/1e6;
    }
    return sum/10.0;
}

static double measure_prim_mat(int** W,int n){
    struct timespec a,b; double sum=0;
    for(int i=0;i<10;i++){
        clock_gettime(CLOCK_MONOTONIC,&a);
        prim_matrix(W,n);
        clock_gettime(CLOCK_MONOTONIC,&b);
        sum += (b.tv_sec-a.tv_sec)*1e3 + (b.tv_nsec-a.tv_nsec)/1e6;
    }
    return sum/10.0;
}

static double measure_prim_csr(CSRGraph* G,int* Wcsr){
    struct timespec a,b; double sum=0;
    for(int i=0;i<10;i++){
        clock_gettime(CLOCK_MONOTONIC,&a);
        prim_csr(G,Wcsr);
        clock_gettime(CLOCK_MONOTONIC,&b);
        sum += (b.tv_sec-a.tv_sec)*1e3 + (b.tv_nsec-a.tv_nsec)/1e6;
    }
    return sum/10.0;
}

int main(void){
    // Topo benchmark
    FILE* ft = fopen("results/toposort.csv","w");
    fprintf(ft,"n,mat_ms,csr_ms\n");
    for(int n=100;n<=1000;n+=50){
        char fn[64]; snprintf(fn,sizeof(fn),"dataset/dag_%d.txt",n);
        int nn; int** M=load_matrix(fn,&nn);
        int* order=malloc(nn*sizeof(int));
        double t_mat = measure((void(*)(int**,int))topo_matrix,M,nn);
        CSRGraph* G = matrix_to_csr(M,nn);
        topo_csr(G,order); // warm-up
        double t_csr = 0;
        for(int i=0;i<10;i++){
            struct timespec a,b;
            clock_gettime(CLOCK_MONOTONIC,&a);
            topo_csr(G,order);
            clock_gettime(CLOCK_MONOTONIC,&b);
            t_csr += (b.tv_sec-a.tv_sec)*1e3 + (b.tv_nsec-a.tv_nsec)/1e6;
        }
        t_csr /= 10.0;
        fprintf(ft,"%d,%.2f,%.2f\n",nn,t_mat,t_csr);
        free(order);
        free_csr(G);
        for(int i=0;i<nn;i++) free(M[i]); free(M);
    }
    fclose(ft);

    // MST benchmark
    FILE* f30 = fopen("results/mst_30.csv","w");
    FILE* f70 = fopen("results/mst_70.csv","w");
    fprintf(f30,"n,mat_ms,csr_ms\n");
    fprintf(f70,"n,mat_ms,csr_ms\n");

    for(int n=100;n<=1000;n+=50){
        for(int pct=30;pct<=70;pct+=40){
            char fn[64]; snprintf(fn,sizeof(fn),"dataset/mst_%d_%d.txt",pct,n);
            int nn; int** W=load_matrix(fn,&nn);

            // flatten CSR weights into a parallel array
            CSRGraph* G = matrix_to_csr(W,nn);
            int* Wcsr = malloc(G->E * sizeof(int));
            { int idx=0;
              for(int u=0;u<nn;u++)
                for(int i=G->row_ptr[u];i<G->row_ptr[u+1];i++)
                  Wcsr[idx++]=W[u][G->col_idx[i]]; }

            double t_mat = measure_prim_mat(W,nn);
            double t_csr = measure_prim_csr(G,Wcsr);

            FILE* fo = (pct==30)?f30:f70;
            fprintf(fo,"%d,%.2f,%.2f\n",nn,t_mat,t_csr);

            free(Wcsr);
            free_csr(G);
            for(int i=0;i<nn;i++) free(W[i]); free(W);
        }
    }
    fclose(f30);
    fclose(f70);
    return 0;
}

