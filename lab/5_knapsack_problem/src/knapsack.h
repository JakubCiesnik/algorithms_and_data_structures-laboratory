#ifndef KNAPSACK_H
#define KNAPSACK_H

typedef struct{
	int (*in_cargo)[2]; // [[value, weight], ...]
	int container_count;
	int capacity;
	int (*out_cargo)[2]; // [[value, weight], ...]
	int value;
	int out_count;
}cargo_problem;

void read_file(const char* filename, cargo_problem *problem);
void read_verification_file(const char *filename, cargo_problem *problem);
void write_file(const char* filename, cargo_problem *problem);
void print_input(cargo_problem *problem);
void print_output(cargo_problem *problem);

void dynamic(cargo_problem *cargo);
void print_matrix(int** matrix, int rows, int cols);
int max(int a, int b);

void greedy_knapsack(cargo_problem *problem);

#endif
