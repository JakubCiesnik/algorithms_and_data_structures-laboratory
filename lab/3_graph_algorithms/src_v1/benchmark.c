// =========================
// src/benchmark.c
//   Fixed: Separate timing for matrix-based topo, list-based topo (adj‐list)
// =========================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// From dag.c:
extern int** load_matrix(const char* filename, int* out_n);
extern int*  topological_sort_matrix(int** mat, int n);

// **New** from dag.c:
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;
extern Node** matrix_to_list(int** matrix, int n);
extern int*         topological_sort_list(Node** adj, int n); // <<< CHANGED

// From mst.c:
extern int   prim_mst_matrix(int** weight, int n);
extern int   prim_mst_list(int** weight, int n);

// ------------------------------------------------------------
// Timing helper for functions returning int* and taking matrix
// ------------------------------------------------------------
static double measure_time_ptr_mat(
    int* (*func)(int**, int),
    int** data, int n, int runs
) {
    struct timespec t0, t1;
    double sum = 0;
    for (int i = 0; i < runs; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int* out = func(data, n);
        (void)out;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        sum += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
    }
    return sum / runs;
}

// ------------------------------------------------------------
// Timing helper for functions returning int* and taking adj‐list
// ------------------------------------------------------------
static double measure_time_ptr_list(
    int* (*func)(Node**, int),    // <<< CHANGED
    Node** data, int n, int runs  // <<< CHANGED
) {
    struct timespec t0, t1;
    double sum = 0;
    for (int i = 0; i < runs; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int* out = func(data, n);  // <<< CHANGED
        (void)out;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        sum += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
    }
    return sum / runs;
}

// ------------------------------------------------------------
// Timing helper for MST (int-returning)
// ------------------------------------------------------------
static double measure_time_int(
    int (*func)(int**, int),
    int** data, int n, int runs
) {
    struct timespec t0, t1;
    double sum = 0;
    for (int i = 0; i < runs; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int out = func(data, n);
        (void)out;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        sum += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
    }
    return sum / runs;
}

int main(void) {
    const int runs = 10;

    // ----- PART I: Topological Sort -----
    FILE* f_ts = fopen("results/toposort.csv", "w");
    if (!f_ts) { perror("fopen toposort.csv"); exit(EXIT_FAILURE); }
    fprintf(f_ts, "n,time_matrix_ms,time_list_ms\n");

    for (int n = 100; n <= 1000; n += 50) {
        char path[64];
        snprintf(path, sizeof(path), "dataset/dag_%d.txt", n);

        int nn;
        int** matrix = load_matrix(path, &nn);

        // Convert ONCE to adjacency list
        Node** adj_list = matrix_to_list(matrix, nn);

        // Time matrix‐based sort
        double t_mat = measure_time_ptr_mat(
            topological_sort_matrix, matrix, nn, runs
        );

        // Time list‐based sort on adj_list
        double t_list = measure_time_ptr_list(               // <<< CHANGED
            topological_sort_list,                       // <<< CHANGED
            adj_list, nn, runs                                // <<< CHANGED
        );

        fprintf(f_ts, "%d,%.2f,%.2f\n", nn, t_mat, t_list);

        // Cleanup
        for (int i = 0; i < nn; i++) {
            free(matrix[i]);
            Node* p = adj_list[i];
            while (p) {
                Node* tmp = p;
                p = p->next;
                free(tmp);
            }
        }
        free(matrix);
        free(adj_list);
    }
    fclose(f_ts);

    // ----- PART II: Minimum Spanning Tree -----
    FILE* f30 = fopen("results/mst_30.csv", "w");
    FILE* f70 = fopen("results/mst_70.csv", "w");
    if (!f30 || !f70) { perror("fopen mst"); exit(EXIT_FAILURE); }

    fprintf(f30, "n,time_matrix_ms,time_list_ms\n");
    fprintf(f70, "n,time_matrix_ms,time_list_ms\n");

    for (int n = 100; n <= 1000; n += 50) {
        for (int d = 30; d <= 70; d += 40) {
            char path[64];
            snprintf(path, sizeof(path), "dataset/mst_%d_%d.txt", d, n);

            int nn;
            int** weight = load_matrix(path, &nn);

            double tm = measure_time_int(prim_mst_matrix, weight, nn, runs);
            double tl = measure_time_int(prim_mst_list,   weight, nn, runs);
            FILE* out = (d == 30) ? f30 : f70;
            fprintf(out, "%d,%.2f,%.2f\n", nn, tm, tl);

            for (int i = 0; i < nn; i++) free(weight[i]);
            free(weight);
        }
    }
    fclose(f30);
    fclose(f70);

    return 0;
}



// // =========================
// // src/benchmark.c
// //   - Benchmark Topological Sort and MST implementations
// //   - No function‐pointer casts; conversion done before timing
// // =========================
//
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
//
// // From dag.c:
// extern int**  load_matrix(const char* filename, int* out_n);
// extern int*   topological_sort_matrix(int** mat, int n);
// extern int*   topological_sort_list(int** mat, int n);
//
// // From mst.c:
// extern int    prim_mst_matrix(int** weight, int n);
// extern int    prim_mst_list(int** weight, int n);
//
// // From dag.c for adjacency‐list conversion & node struct:
// typedef struct ListNode {
//     int dest;
//     struct ListNode* next;
// } ListNode;
// extern ListNode** matrix_to_list(int** matrix, int n);
//
// // ----------------------------------------------------------------------------
// // Timing helper for functions that return int* (topo sorts)
// // ----------------------------------------------------------------------------
// static double measure_time_ptr(
//     int* (*func)(int**, int),
//     int** data, int n, int runs
// ) {
//     struct timespec t0, t1;
//     double sum = 0;
//     for (int i = 0; i < runs; i++) {
//         clock_gettime(CLOCK_MONOTONIC, &t0);
//         int* result = func(data, n);
//         (void)result;  // discard
//         clock_gettime(CLOCK_MONOTONIC, &t1);
//         sum += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
//     }
//     return sum / runs;
// }
//
// // ----------------------------------------------------------------------------
// // Timing helper for functions that return int (MSTs)
// // ----------------------------------------------------------------------------
// static double measure_time_int(
//     int (*func)(int**, int),
//     int** data, int n, int runs
// ) {
//     struct timespec t0, t1;
//     double sum = 0;
//     for (int i = 0; i < runs; i++) {
//         clock_gettime(CLOCK_MONOTONIC, &t0);
//         int result = func(data, n);
//         (void)result;  // discard
//         clock_gettime(CLOCK_MONOTONIC, &t1);
//         sum += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
//     }
//     return sum / runs;
// }
//
// int main(void) {
//     const int runs = 10;
//
//     // --------
//     // PART I: Topological Sort
//     // --------
//     FILE* f_ts = fopen("results/toposort.csv", "w");
//     if (!f_ts) { perror("fopen toposort.csv"); exit(EXIT_FAILURE); }
//     fprintf(f_ts, "n,time_matrix_ms,time_list_ms\n");
//
//     for (int n = 100; n <= 1000; n += 50) {
//         char path[64];
//         snprintf(path, sizeof(path), "dataset/dag_%d.txt", n);
//
//         int nn;
//         int** matrix = load_matrix(path, &nn);
//
//         // Convert *once* outside timing
//         ListNode** adj_list = matrix_to_list(matrix, nn);
//
//         // Time matrix-based topological sort
//         double t_mat = measure_time_ptr(
//             topological_sort_matrix, matrix, nn, runs
//         );
//
//         // Time list-based topological sort
//         double t_lst = measure_time_ptr(
//             topological_sort_list, matrix, nn, runs
//         );
//
//         fprintf(f_ts, "%d,%.2f,%.2f\n", nn, t_mat, t_lst);
//
//         // Cleanup
//         for (int i = 0; i < nn; i++) {
//             free(matrix[i]);
//             // free adjacency list nodes
//             ListNode* p = adj_list[i];
//             while (p) {
//                 ListNode* tmp = p;
//                 p = p->next;
//                 free(tmp);
//             }
//         }
//         free(matrix);
//         free(adj_list);
//     }
//     fclose(f_ts);
//
//     // --------
//     // PART II: MST
//     // --------
//     FILE* f30 = fopen("results/mst_30.csv", "w");
//     FILE* f70 = fopen("results/mst_70.csv", "w");
//     if (!f30 || !f70) { perror("fopen mst csv"); exit(EXIT_FAILURE); }
//     fprintf(f30, "n,time_matrix_ms,time_list_ms\n");
//     fprintf(f70, "n,time_matrix_ms,time_list_ms\n");
//
//     for (int n = 100; n <= 1000; n += 50) {
//         for (int d = 30; d <= 70; d += 40) {
//             char path[64];
//             snprintf(path, sizeof(path), "dataset/mst_%d_%d.txt", d, n);
//
//             int nn;
//             int** weight = load_matrix(path, &nn);
//
//             double tm = measure_time_int(
//                 prim_mst_matrix, weight, nn, runs
//             );
//             double tl = measure_time_int(
//                 prim_mst_list, weight, nn, runs
//             );
//
//             FILE* out = (d == 30) ? f30 : f70;
//             fprintf(out, "%d,%.2f,%.2f\n", nn, tm, tl);
//
//             for (int i = 0; i < nn; i++) free(weight[i]);
//             free(weight);
//         }
//     }
//     fclose(f30);
//     fclose(f70);
//
//     return 0;
// }
//
// // // #include "dag.c"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <time.h>
// //
// //
// //
// //
// // // =========================
// // // src/benchmark.c
// // //   - Benchmark Topological Sort and MST implementations
// // //   - Ensures conversion to list is done *before* timing
// // // =========================
// //
// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <time.h>
// //
// // // Externally implemented in dag.c and mst.c:
// // extern int**    load_matrix(const char* filename, int* out_n);
// // extern void     store_matrix(const char* filename, int** mat, int n);
// //
// // // Topo sort functions from dag.c
// // extern int*     topological_sort_matrix(int** mat, int n);
// // extern int*     topological_sort_list(int** mat, int n);
// //
// // // MST functions from mst.c
// // extern int      prim_mst_matrix(int** weight, int n);
// // extern int      prim_mst_list(int** weight, int n);
// //
// // // New conversion function from dag.c
// // extern struct ListNode {
// //     int dest;
// //     struct ListNode* next;
// // } ** matrix_to_list(int** matrix, int n);
// //
// // // Utility: measure a void(int**,int) function over `runs` iterations
// // static double measure_time(
// //     void (*func)(int**, int),
// //     int** data, int n,
// //     int runs
// // ) {
// //     struct timespec t0, t1;
// //     double total_ms = 0.0;
// //
// //     for (int i = 0; i < runs; i++) {
// //         clock_gettime(CLOCK_MONOTONIC, &t0);
// //         func(data, n);
// //         clock_gettime(CLOCK_MONOTONIC, &t1);
// //
// //         double elapsed = (t1.tv_sec  - t0.tv_sec ) * 1e3
// //                        + (t1.tv_nsec - t0.tv_nsec) / 1e6;
// //         total_ms += elapsed;
// //     }
// //     return total_ms / runs;
// // }
// //
// // int main(void) {
// //     const int runs = 10;
// //
// //     // ------------------------
// //     // PART I: Topological Sort
//     // ------------------------
//     FILE* fout_ts = fopen("results/toposort.csv", "w");
//     if (!fout_ts) { perror("fopen toposort.csv"); exit(EXIT_FAILURE); }
//     fprintf(fout_ts, "n,time_matrix_ms,time_list_ms\n");
//
//     for (int n = 100; n <= 1000; n += 50) {
//         char path[64];
//         snprintf(path, sizeof(path), "dataset/dag_%d.txt", n);
//
//         // 1) Load adjacency matrix
//         int nn;
//         int** matrix = load_matrix(path, &nn);
//
//         // 2) Convert to adjacency list ONCE, *before* timing
//         struct ListNode** adj_list = matrix_to_list(matrix, nn);
//
//         // --- Benchmark the matrix-based topological sort ---
//         double t_matrix = measure_time(
//             /* func */ (void(*)(int**,int)) topological_sort_matrix,
//             /* data */ matrix, nn, runs
//         );
//
//         // --- Benchmark the list-based topological sort ---
//         double t_list = measure_time(
//             /* func */ (void(*)(int**,int)) topological_sort_list,
//             /* data */ matrix, nn, runs
//         );
//
//         fprintf(fout_ts, "%d,%.2f,%.2f\n", nn, t_matrix, t_list);
//
//         // Cleanup
//         for (int i = 0; i < nn; i++) {
//             free(matrix[i]);
//             // also free adj_list[i] chain
//             struct ListNode* p = adj_list[i];
//             while (p) {
//                 struct ListNode* tmp = p;
//                 p = p->next;
//                 free(tmp);
//             }
//         }
//         free(matrix);
//         free(adj_list);
//     }
//     fclose(fout_ts);
//
//
//     // ----------------------
//     // PART II: Minimum Spanning Tree
//     // ----------------------
//     FILE* fout30 = fopen("results/mst_30.csv", "w");
//     FILE* fout70 = fopen("results/mst_70.csv", "w");
//     if (!fout30 || !fout70) { perror("fopen mst_*.csv"); exit(EXIT_FAILURE); }
//     fprintf(fout30, "n,time_matrix_ms,time_list_ms\n");
//     fprintf(fout70, "n,time_matrix_ms,time_list_ms\n");
//
//     for (int n = 100; n <= 1000; n += 50) {
//         for (int d = 30; d <= 70; d += 40) {
//             char path[64];
//             snprintf(path, sizeof(path),
//                      "dataset/mst_%d_%d.txt", d, n);
//
//             // 1) Load weighted adjacency matrix
//             int nn;
//             int** weight = load_matrix(path, &nn);
//
//             // No list conversion here—in prim_mst_list we internally
//             // call matrix_to_list *before* the timed loops.
//
//             // 2) Benchmark matrix-based Prim’s
//             double t_mat = measure_time(
//                 (void(*)(int**,int)) prim_mst_matrix,
//                 weight, nn, runs
//             );
//
//             // 3) Benchmark list-based Prim’s
//             double t_lst = measure_time(
//                 (void(*)(int**,int)) prim_mst_list,
//                 weight, nn, runs
//             );
//
//             FILE* out = (d == 30) ? fout30 : fout70;
//             fprintf(out, "%d,%.2f,%.2f\n", nn, t_mat, t_lst);
//
//             // Cleanup
//             for (int i = 0; i < nn; i++) free(weight[i]);
//             free(weight);
//         }
//     }
//     fclose(fout30);
//     fclose(fout70);
//
//     return 0;
// }
// // // Externally defined from dag.c and mst.c
// // extern int** load_matrix(const char*, int*);
// // extern int   prim_mst_matrix(int**, int);
// // extern int   prim_mst_list(int**, int);
// // extern int*  topological_sort_matrix(int**, int);
// // extern int*  topological_sort_list(int**, int);
// //
// // // For topological-sort fns returning int*
// // static double measure_time_tsort(int* (*f)(int**,int), int** mat, int n) {
// //     struct timespec t0, t1;
// //     double total = 0;
// //     for (int i = 0; i < 10; i++) {
// //         clock_gettime(CLOCK_MONOTONIC, &t0);
// //         int* tmp = f(mat,n);        // call returning int*
// //         free(tmp);                  // clean up the returned array
// //         clock_gettime(CLOCK_MONOTONIC, &t1);
// //         total += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
// //     }
// //     return total/10.0;
// // }
// //
// // // For MST fns returning int
// // static double measure_time_mst(int (*f)(int**,int), int** mat, int n) {
// //     struct timespec t0, t1;
// //     double total = 0;
// //     for (int i = 0; i < 10; i++) {
// //         clock_gettime(CLOCK_MONOTONIC, &t0);
// //         (void)f(mat,n);             // call returning int, ignore result
// //         clock_gettime(CLOCK_MONOTONIC, &t1);
// //         total += (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
// //     }
// //     return total/10.0;
// // }
// //
// //
// // int main(void) {
// //     FILE* ft = fopen("results/toposort.csv", "w");
// //     fprintf(ft, "n,time_matrix_ms,time_list_ms\n");
// //     for (int n = 100; n <= 1000; n += 50) {
// //         char path[64];
// //         snprintf(path, sizeof(path), "dataset/dag_%d.txt", n);
// //         int nn;
// //         int** mat = load_matrix(path, &nn);
// //
// //         // ----- START PATCH -----
// //         // Convert the adjacency matrix to an adjacency list once,
// //         // so that we do NOT include this cost in the timing.
// //         ListNode** adj_list = matrix_to_list(mat, nn);
// //         // -----   END PATCH   -----
// //
// //         // Time the matrix-based topological sort
// //         double tm = measure_time(topological_sort_matrix, mat, nn);
// //
// //         // Time the list-based topological sort (using pre-built list)
// //         // We'll need a separate timing function that accepts ListNode**:
// //         double tl = 0.0;
// //         for (int run = 0; run < 10; ++run) {
// //             struct timespec t0, t1;
// //             clock_gettime(CLOCK_MONOTONIC, &t0);
// //             topological_sort_list(adj_list, nn);
// //             clock_gettime(CLOCK_MONOTONIC, &t1);
// //             tl += (t1.tv_sec - t0.tv_sec) * 1e3
// //                 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
// //         }
// //         tl /= 10.0;
// //
// //         // Free the adjacency list after timing
// //         for (int i = 0; i < nn; ++i) {
// //             ListNode* p = adj_list[i];
// //             while (p) { ListNode* tmp = p; p = p->next; free(tmp); }
// //         }
// //         free(adj_list);
// //         fprintf(ft, "%d,%.2f,%.2f\n", nn, tm, tl);
// //
// //         for (int i = 0; i < nn; i++) free(mat[i]);
// //         free(mat);
// //     }
// //     fclose(ft);
// //
// //     // — MST Benchmarks (30% & 70%) —
// //     FILE* f30 = fopen("results/mst_30.csv", "w");
// //     FILE* f70 = fopen("results/mst_70.csv", "w");
// //     fprintf(f30, "n,time_matrix_ms,time_list_ms\n");
// //     fprintf(f70, "n,time_matrix_ms,time_list_ms\n");
// //
// //     for (int n = 100; n <= 1000; n += 50) {
// //         for (int d = 30; d <= 70; d += 40) {
// //             char path[64];
// //             snprintf(path, sizeof(path), "dataset/mst_%d_%d.txt", d, n);
// //
// //             int nn;
// //             int** w = load_matrix(path, &nn);
// //
// //             double tm = measure_time_mst(prim_mst_matrix, w, nn);
// //             double tl = measure_time_mst(prim_mst_list,   w, nn);
// //
// //             FILE* out = (d == 30) ? f30 : f70;
// //             fprintf(out, "%d,%.2f,%.2f\n", nn, tm, tl);
// //
// //             for (int i = 0; i < nn; i++) free(w[i]);
// //             free(w);
// //         }
// //     }
// //     fclose(f30);
// //     fclose(f70);
// //
// //     return 0;
// // }
// //
