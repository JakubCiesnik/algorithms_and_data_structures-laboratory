#include <stdio.h>
#include <stdlib.h>
#include "knapsack.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    cargo_problem problem;
    read_file(argv[1], &problem);

    print_input(&problem);
    greedy_knapsack(&problem);
    print_output(&problem);
  
    write_file(argv[2], &problem);

    // Free output cargo memory
    if (problem.out_cargo != NULL) {
        // CORRECTED: use out_count instead of container_count
        for (int i = 0; i < problem.out_count; i++) {
            free(problem.out_cargo[i]);
        }
        free(problem.out_cargo);
    }

    // Free input cargo memory
    for (int i = 0; i < problem.container_count; i++) {
        free(problem.in_cargo[i]);
    }
    free(problem.in_cargo);

    return 0;
}
