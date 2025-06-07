#include <stdlib.h>
#include <stdio.h>
#include "knapsack.h"

static int compare_items(const void *a, const void *b) {
    const int *itemA = *(const int **)a;
    const int *itemB = *(const int **)b;
    
    double densityA = (double)itemA[0] / itemA[1];
    double densityB = (double)itemB[0] / itemB[1];
    
    if (densityA > densityB) return -1;
    if (densityA < densityB) return 1;
    return 0;
}

void greedy_knapsack(cargo_problem *problem) {
    int n = problem->container_count;
    int capacity = problem->capacity;
    
    // Reset solution
    if (problem->out_cargo != NULL) {
        for (int i = 0; i < problem->out_count; i++) {
            free(problem->out_cargo[i]);
        }
        free(problem->out_cargo);
    }
    problem->out_cargo = NULL;
    problem->out_count = 0;
    problem->value = 0;
    
    // Create a copy of the input array for sorting
    int **items = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        items[i] = malloc(2 * sizeof(int));
        items[i][0] = problem->in_cargo[i][0];  // value
        items[i][1] = problem->in_cargo[i][1];  // weight
    }
    
    // Sort items by value density (value/weight) descending
    qsort(items, n, sizeof(int *), compare_items);
    
    // Greedy selection
    int current_weight = 0;
    int total_value = 0;
    int selected_count = 0;
    int **selected = malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        if (current_weight + items[i][1] <= capacity) {
            // Add item to selection
            selected[selected_count] = malloc(2 * sizeof(int));
            selected[selected_count][0] = items[i][0];
            selected[selected_count][1] = items[i][1];
            
            current_weight += items[i][1];
            total_value += items[i][0];
            selected_count++;
        }
    }
    
    // Save results
    problem->out_cargo = malloc(selected_count * sizeof(int *));
    for (int i = 0; i < selected_count; i++) {
        problem->out_cargo[i] = selected[i];
    }
    problem->out_count = selected_count;
    problem->value = total_value;
    
    // Cleanup
    for (int i = 0; i < n; i++) {
        free(items[i]);
    }
    free(items);
    free(selected);
}
