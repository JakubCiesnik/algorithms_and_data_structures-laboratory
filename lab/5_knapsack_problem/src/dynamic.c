// #include "knapsack.h"
// #include <stdlib.h>

// // Functions
// void dynamic(cargo_problem cargo){
//     // Variables
//     int cap = cargo.capacity;
//     int cc = cargo.container_count;

//     // Create dynamic 2D matrix
//     int** matrix;
//     matrix = malloc((cc + 1)*sizeof(*matrix));

//     for (int i = 0; i < cc + 1; i++)
//     {
//         matrix[i] = malloc((cap + 1)*sizeof(matrix[i]));
//     }

//     // Populate matrix
//     for (int i = 0; i < cc + 1; i++)
//     {
//         for (int j = 0; j < cap + 1; j++)
//         {
//             matrix[i][j] = 0;
//         }
        
//     }

// }

#include "knapsack.h"
#include <stdlib.h>

// Functions
void dynamic(cargo_problem cargo){
    // Variables
    int cap = cargo.capacity;
    int cc = cargo.container_count;

    // Create dynamic 2D matrix
    int** matrix;
    matrix = calloc(cc + 1, sizeof(*matrix));

    for (int i = 0; i < cc + 1; i++)
    {
        matrix[i] = calloc(cap + 1, sizeof(matrix[i]));
    }

    // Populate matrix
    for (int i = 0; i < cc + 1; i++)
    {
        for (int j = 0; j < cap + 1; j++)
        {
            matrix[i][j] = 0;
        }
        
    }


    
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