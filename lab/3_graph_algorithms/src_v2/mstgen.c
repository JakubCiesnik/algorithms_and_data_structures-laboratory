// =========================
// Generate Connected MST Graphs
// =========================
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void store_matrix(const char*, int**, int);

static int** make_mst_graph(int n, double d){
    int maxe=n*(n-1)/2;
    int target=(int)ceil(d*maxe);
    int** W=calloc(n,sizeof(int*));
    for(int i=0;i<n;i++) W[i]=calloc(n,sizeof(int));

    // chain
    for(int i=0;i<n-1;i++){
        int wt=rand()%1000+1;
        W[i][i+1]=W[i+1][i]=wt;
    }
    int cnt=n-1;
    while(cnt<target){
        int u=rand()%n, v=rand()%n;
        if(u!=v && !W[u][v]){
            int wt=rand()%1000+1;
            W[u][v]=W[v][u]=wt;
            cnt++;
        }
    }
    return W;
}

int main(void){
    srand((unsigned)time(NULL));
    for(int n=100;n<=1000;n+=50){
        for(int pct=30;pct<=70;pct+=40){
            double d=pct/100.0;
            int** W=make_mst_graph(n,d);
            char fn[64];
            snprintf(fn,sizeof(fn),"dataset/mst_%d_%d.txt",pct,n);
            store_matrix(fn,W,n);
            for(int i=0;i<n;i++) free(W[i]);
            free(W);
        }
    }
    return 0;
}

