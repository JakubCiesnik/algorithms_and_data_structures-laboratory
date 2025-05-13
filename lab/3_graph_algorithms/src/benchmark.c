#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Externally defined from dag.c and mst.c
extern int** load_matrix(const char*, int*);
extern int   prim_mst_matrix(int**, int);
extern int   prim_mst_list(int**, int);
extern int*  topological_sort_matrix(int**, int);
extern int*  topological_sort_list(int**, int);

// For topological-sort fns returning int*
static double measure_time_tsort(int* (*f)(int**,int), int** mat, int n) {
    struct timespec t0, t1;
    double total = 0;
    for (int i = 0; i < 10; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int* tmp = f(mat,n);        // call returning int*
        free(tmp);                  // clean up the returned array
        clock_gettime(CLOCK_MONOTONIC, &t1);
        total += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
    }
    return total/10.0;
}

// For MST fns returning int
static double measure_time_mst(int (*f)(int**,int), int** mat, int n) {
    struct timespec t0, t1;
    double total = 0;
    for (int i = 0; i < 10; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        (void)f(mat,n);             // call returning int, ignore result
        clock_gettime(CLOCK_MONOTONIC, &t1);
        total += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
    }
    return total/10.0;
}


int main(void) {
    // — Topological Sort Benchmarks —
    FILE* ft = fopen("results/toposort.csv", "w");
    fprintf(ft, "n,time_matrix_ms,time_list_ms\n");
    for (int n = 100; n <= 1000; n += 50) {
        char path[64];
        snprintf(path, sizeof(path), "dataset/dag_%d.txt", n);

        int nn; 
        int** mat = load_matrix(path, &nn);

        double tm = measure_time_tsort(topological_sort_matrix, mat, nn);
        double tl = measure_time_tsort(topological_sort_list,   mat, nn);
        fprintf(ft, "%d,%.2f,%.2f\n", nn, tm, tl);

        for (int i = 0; i < nn; i++) free(mat[i]);
        free(mat);
    }
    fclose(ft);

    // — MST Benchmarks (30% & 70%) —
    FILE* f30 = fopen("results/mst_30.csv", "w");
    FILE* f70 = fopen("results/mst_70.csv", "w");
    fprintf(f30, "n,time_matrix_ms,time_list_ms\n");
    fprintf(f70, "n,time_matrix_ms,time_list_ms\n");

    for (int n = 100; n <= 1000; n += 50) {
        for (int d = 30; d <= 70; d += 40) {
            char path[64];
            snprintf(path, sizeof(path), "dataset/mst_%d_%d.txt", d, n);

            int nn;
            int** w = load_matrix(path, &nn);

            double tm = measure_time_mst(prim_mst_matrix, w, nn);
            double tl = measure_time_mst(prim_mst_list,   w, nn);

            FILE* out = (d == 30) ? f30 : f70;
            fprintf(out, "%d,%.2f,%.2f\n", nn, tm, tl);

            for (int i = 0; i < nn; i++) free(w[i]);
            free(w);
        }
    }
    fclose(f30);
    fclose(f70);

    return 0;
}

