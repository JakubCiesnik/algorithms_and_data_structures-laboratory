#define _POSIX_C_SOURCE 199309L
#include "dag.h"
#include "mst.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// --- timing helper ---
static double diff_ms(const struct timespec *a, const struct timespec *b) {
    return (b->tv_sec - a->tv_sec) * 1e3 +
           (b->tv_nsec - a->tv_nsec) / 1e6;
}

// --- Topo sort benchmark ---
static void bench_tsort(int ***pmats, AdjNode ***plists, int count, const char *outname) {
    FILE *f = fopen(outname, "w");
    fprintf(f, "n,time_matrix_ms,time_list_ms\n");
    int *order = malloc(15000 * sizeof *order);  // Allocate for the maximum n (15000)
    for (int i = 0; i < count; i++) {
        int n = 1000 + i * 1000;  // Use n values starting from 1000 and incrementing by 1000
        int **mat = pmats[i];
        AdjNode **lst = plists[i];
        struct timespec t0, t1;
        double sum_m = 0, sum_l = 0;
        for (int it = 0; it < 10; it++) {
            clock_gettime(CLOCK_MONOTONIC, &t0);
            topo_sort_matrix(mat, n, order);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            sum_m += diff_ms(&t0, &t1);

            clock_gettime(CLOCK_MONOTONIC, &t0);
            topo_sort_list(lst, n, order);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            sum_l += diff_ms(&t0, &t1);
        }
        fprintf(f, "%d,%.3f,%.3f\n", n, sum_m/10.0, sum_l/10.0);
    }
    free(order);
    fclose(f);
}

// --- MST benchmark ---
static void bench_mst(int **mats[], int count, const char *outname) {
    FILE *f = fopen(outname, "w");
    fprintf(f, "n,time_matrix_ms,time_list_ms\n");
    for (int i = 0; i < count; i++) {
        int n = 1000 + i * 1000;  // Use n values starting from 1000 and incrementing by 1000
        int **mat = mats[i];
        struct timespec t0, t1;
        double sum_m = 0, sum_l = 0;
        for (int it = 0; it < 10; it++) {
            clock_gettime(CLOCK_MONOTONIC, &t0);
            prim_matrix(mat, n);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            sum_m += diff_ms(&t0, &t1);

            clock_gettime(CLOCK_MONOTONIC, &t0);
            prim_list(mat, n);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            sum_l += diff_ms(&t0, &t1);
        }
        fprintf(f, "%d,%.3f,%.3f\n", n, sum_m/10.0, sum_l/10.0);
    }
    fclose(f);
}

int main(void) {
    const int count = (15000 - 1000) / 1000 + 1;  // Now works with n = 1000, 2000, ..., 15000

    // --- Preload DAG datasets ---
    int **dmats[count];
    AdjNode **dlists[count];
    for (int i = 0; i < count; i++) {
        int n = 1000 + i * 1000;  // Use n values starting from 1000 and incrementing by 1000
        char fname[256];
        snprintf(fname, sizeof(fname), "dataset/dag_%d.txt", n);
        int nn;
        dmats[i] = load_matrix(fname, &nn);
        dlists[i] = matrix_to_list(dmats[i], nn, 0);
    }
    bench_tsort(dmats, dlists, count, "results/toposort.csv");
    // free DAG
    for (int i = 0; i < count; i++) {
        int n = 1000 + i * 1000;
        free_matrix(dmats[i], n);
        free_adjlist(dlists[i], n);
    }

    // --- Preload MST datasets & benchmark ---
    double densities[2] = {0.30, 0.70};
    for (int d = 0; d < 2; d++) {
        int **mmats[count];
        int pct = (int)(densities[d]*100);
        for (int i = 0; i < count; i++) {
            int n = 1000 + i * 1000;  // Use n values starting from 1000 and incrementing by 1000
            char fname[256];
            snprintf(fname, sizeof(fname), "dataset/mst_%02d_%d.txt", pct, n);
            int nn;
            mmats[i] = load_matrix(fname, &nn);
        }
        char out[256];
        snprintf(out, sizeof(out), "results/mst_%02d.csv", pct);
        bench_mst(mmats, count, out);
        for (int i = 0; i < count; i++) {
            int n = 1000 + i * 1000;
            free_matrix(mmats[i], n);
        }
    }

    return 0;
}
