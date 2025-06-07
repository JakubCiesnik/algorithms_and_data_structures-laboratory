#ifndef KNAPSACK_H
#define KNAPSACK_H

typedef struct{
	int** in_cargo;
	int container_count;
	int capacity;
	int** out_cargo;
	int value;
}cargo_problem;


void dynamic(cargo_problem cargo);
void print_matrix(int** matrix);


#endif