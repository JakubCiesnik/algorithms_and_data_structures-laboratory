// =========================
// Generate Connected DAGs
// =========================
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void store_matrix(const char*, int**, int);

// make a random DAG with 60% of edges, connected via backbone
static int** make_dag(int n){
    int maxe=n*(n-1)/2;
    int target=(int)ceil(0.6*maxe);
    int** M=calloc(n,sizeof(int*));
    for(int i=0;i<n;i++) M[i]=calloc(n,sizeof(int));

    // random topological order
    int* ord=malloc(n*sizeof(int));
    for(int i=0;i<n;i++) ord[i]=i;
    for(int i=n-1;i>0;i--){
        int j=rand()%(i+1);
        int t=ord[i]; ord[i]=ord[j]; ord[j]=t;
    }
    // backbone
    for(int i=0;i<n-1;i++){
        M[ord[i]][ord[i+1]] = 1;
    }
    int cnt=n-1;
    // random forward edges
    while(cnt<target){
        int i=rand()%n, j=rand()%n;
        if(i<j && !M[ord[i]][ord[j]]){
            M[ord[i]][ord[j]] = 1;
            cnt++;
        }
    }
    free(ord);
    return M;
}

int main(void){
    srand((unsigned)time(NULL));
    for(int n=100;n<=1000;n+=50){
        int** M = make_dag(n);
        char fn[64]; snprintf(fn,sizeof(fn),"dataset/dag_%d.txt",n);
        store_matrix(fn,M,n);
        for(int i=0;i<n;i++) free(M[i]);
        free(M);
    }
    return 0;
}

