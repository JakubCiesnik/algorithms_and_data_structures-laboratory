#include <stdio.h>
#include <stdlib.h>
#include "knapsack.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    cargo_problem* cargo = malloc(sizeof(*cargo));

    read_verification_file(argv[1], cargo);

    // DEBUG
    // print_input(cargo);
    printf("Greedy algo output:\n");
    greedy_knapsack(cargo);
    print_output(cargo);
    
    printf("\nDynamic algo output:\n");
    dynamic(cargo);
    print_output(cargo);

    // Free cargo memory
    free(cargo->out_cargo);
    free(cargo->in_cargo);
    free(cargo);

    return 0;
}
