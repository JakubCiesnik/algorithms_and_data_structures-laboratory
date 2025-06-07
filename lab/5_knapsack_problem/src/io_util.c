#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knapsack.h"

void read_file(const char *filename, cargo_problem *problem) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d,%d", &problem->container_count, &problem->capacity) != 2) {
        fprintf(stderr, "Invalid first line format.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    problem->in_cargo = malloc(problem->container_count * sizeof(int *));
    if (!problem->in_cargo) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < problem->container_count; i++) {
        problem->in_cargo[i] = malloc(2 * sizeof(int));
        if (!problem->in_cargo[i]) {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++) {
                free(problem->in_cargo[j]);
            }
            free(problem->in_cargo);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (fscanf(file, "%d,%d", &problem->in_cargo[i][0], &problem->in_cargo[i][1]) != 2) {
            fprintf(stderr, "Invalid data at line %d.\n", i + 2);
            for (int j = 0; j <= i; j++) {
                free(problem->in_cargo[j]);
            }
            free(problem->in_cargo);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    // Initialize solution fields
    problem->out_cargo = NULL;
    problem->out_count = 0;
    problem->value = 0;

    fclose(file);
}

void write_file(const char *filename, cargo_problem *problem) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d,%d\n", problem->container_count, problem->capacity);

    for (int i = 0; i < problem->container_count; i++) {
        fprintf(file, "%d,%d\n", problem->in_cargo[i][0], problem->in_cargo[i][1]);
    }

    fclose(file);
}

void print_input(cargo_problem *problem) {
    printf("Input items: %d, Capacity: %d\n", problem->container_count, problem->capacity);
    for (int i = 0; i < problem->container_count; i++) {
        printf("Item %d: value=%d, weight=%d\n", i+1, problem->in_cargo[i][0], problem->in_cargo[i][1]);
    }
}

void print_output(cargo_problem *problem) {
    printf("Total value: %d, Capacity used: ", problem->value);
    
    // Calculate total weight used
    int total_weight = 0;
    for (int i = 0; i < problem->out_count; i++) {
        total_weight += problem->out_cargo[i][1];
    }
    printf("%d/%d\n", total_weight, problem->capacity);

    printf("Selected items: %d\n", problem->out_count);
    for (int i = 0; i < problem->out_count; i++) {
        printf("Item %d: value=%d, weight=%d\n", i+1, 
               problem->out_cargo[i][0], problem->out_cargo[i][1]);
    }
}
