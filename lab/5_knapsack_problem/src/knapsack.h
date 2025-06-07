struct cargo_problem {
  int** in_cargo; // [[value, weight], ...]
  int container_count;
  int capacity;
  int** out_cargo; // [[value, weight], ...]
  int value;
  int out_count;
};

void read_file(const char* filename, struct cargo_problem *problem);
void write_file(const char* filename, struct cargo_problem *problem);
void print_input(struct cargo_problem *problem);
void print_output(struct cargo_problem *problem);
