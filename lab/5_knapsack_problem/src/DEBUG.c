#include "knapsack.h"
#include <stdio.h>

int main(){

    // Example cargo
    cargo_problem cargo = {
        {
            {1, 2},
            {2, 3},
            {3, 4}
        }, 
        3, 
        7, 
        {{0}}, 
        0
    };
    
    // Debug dynamic knapsack
    dynamic(cargo);

    
    int rows = 2;
    int cols = 5;
    int** matrix = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = calloc(cols, sizeof(int));
    }

    print_matrix(matrix);

    return 0;
}
