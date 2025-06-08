#include "knapsack.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Functions
void dynamic(cargo_problem* cargo){
    // Variables
    int cc = cargo->container_count;
    int cap = cargo->capacity;
    int mat_rows = cc + 1;
    int mat_cols = cap + 1;

    // Create dynamic 2D matrix
    int** matrix;
    matrix = malloc(mat_rows * sizeof(*matrix));
    for (int i = 0; i < mat_rows; i++)
    {
        matrix[i] = calloc(mat_cols, sizeof(int));
    }
    
    // Calc values
    for (int i = 1; i < mat_rows; i++)
    {
        for (int j = 1; j < mat_cols; j++)
        {
            // if it doesnt fit
            if (cargo->in_cargo[i-1][1] > j){
                matrix[i][j] = matrix[i-1][j];
            }
            else{
                int val1 = matrix[i-1][j];
                int val2 = matrix[i-1][j - cargo->in_cargo[i-1][1]] + cargo->in_cargo[i-1][0];
                matrix[i][j] = max(val1, val2);
            }
        }
    }
    
    // DEBUG
    // print_matrix(matrix, mat_rows, mat_cols);

    // Return most optimal items
    cargo->value = matrix[cc][cap];
    cargo->out_cargo = malloc(cc * sizeof(int*));
    cargo->out_count = 0;

    int i = cc;
    int j = cap;
    
    while (matrix[i][j] != 0 && j >= 0){
        if (matrix[i][j] == matrix[i-1][j]){
            i--;
        }
        else{
            cargo->out_cargo[cargo->out_count][0] = cargo->in_cargo[i-1][0];
            cargo->out_cargo[cargo->out_count][1] = cargo->in_cargo[i-1][1];
            cargo->out_count++;

            j -= cargo->in_cargo[i-1][1];
            i--;
        }
    }

    // Cleanup
    for (int i = 0; i <= cc; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void print_matrix(int** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%i ", matrix[i][j]);
        }
    printf("\n");
    }
}

int max(int a, int b){
    return (a > b ? a : b);
}