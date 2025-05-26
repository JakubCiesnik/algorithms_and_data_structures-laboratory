#include "def_graph.h"
#include "euler_check.h"
#include "hamilton_check.h"
#include "graph_generator.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    srand(time(NULL));
    int n_values[15] = {
        200, 400, 600, 800, 1000,
        1200, 1400, 1600, 1800, 2000,
        2200, 2400, 2600, 2800, 3000
    };
    double densities[2] = {0.3, 0.7};
    const char* density_labels[2] = {"sparse","dense"};
    FILE* f = fopen("results.csv", "w");
    fprintf(f, "n,density,euler_time,hamilton_time\n");
    printf("%-8s %-8s %-15s %-15s\n", "n", "density", "euler_time[s]", "hamilton_time[s]");
    for (int d = 0; d < 2; d++) {
        for (int idx = 0; idx < 15; idx++) {
            int n = n_values[idx];
            Graph* g = create_graph(n, false, false);
            generate_euler_hamilton_graph(g, n, densities[d]);
            EulerGraph eg = {0};
            eg.n = g->num_nodes;
            for (int i = 0; i < g->num_nodes; i++)
                for (int j = 0; j < g->num_nodes; j++)
                    eg.matrix[i][j] = g->adj_matrix[i][j];
            HamiltonGraph hg = {0};
            hg.n = g->num_nodes;
            for (int i = 0; i < g->num_nodes; i++)
                for (int j = 0; j < g->num_nodes; j++)
                    hg.matrix[i][j] = g->adj_matrix[i][j] ? 1 : 0;
            clock_t t1 = clock();
            if (is_eulerian_graph(&eg)) {
                // Suppress printing the Eulerian cycle for benchmarking
                // euler_cycle(&eg, 0);
            }
            clock_t t2 = clock();

            hamilton_cycle(&hg);

            clock_t t3 = clock();
            double euler_time = (double)(t2-t1)/CLOCKS_PER_SEC;
            double hamilton_time = (double)(t3-t2)/CLOCKS_PER_SEC;
            fprintf(f, "%d,%s,%f,%f\n", n, density_labels[d], euler_time, hamilton_time);
            printf("%-8d %-8s %-15.8f %-15.8f\n", n, density_labels[d], euler_time, hamilton_time);
            free_graph(g);
        }
    }
    
    fclose(f);
    printf("Saved to: 'results.csv' \n");
    
    return 0;
}
