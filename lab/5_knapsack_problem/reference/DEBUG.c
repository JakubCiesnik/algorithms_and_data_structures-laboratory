#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    int cap = 7;
    int cc = 4;

    // Example cargo
    cargo_problem* cargo = malloc(sizeof(*cargo));
    cargo->capacity = 7;
    cargo->container_count = 4;

    cargo->in_cargo = malloc(cc * 2 * sizeof(int));
    cargo->in_cargo[0][0] = 1; 
    cargo->in_cargo[0][1] = 2;
    cargo->in_cargo[1][0] = 3; 
    cargo->in_cargo[1][1] = 2;
    cargo->in_cargo[2][0] = 4; 
    cargo->in_cargo[2][1] = 3;
    cargo->in_cargo[3][0] = 1; 
    cargo->in_cargo[3][1] = 3;
    
    // Debug dynamic knapsack
    dynamic(cargo);

    printf("%d\n", cargo->value);
    for (int i = 0; i < cargo->out_count; i++)
    {
        printf("(%d, ", cargo->out_cargo[i][0]);
        printf("%d),\n", cargo->out_cargo[i][1]);
    }
    
    free(cargo->in_cargo);
    free(cargo->out_cargo);
    free(cargo);

    return 0;
}
