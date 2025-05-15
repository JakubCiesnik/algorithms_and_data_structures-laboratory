CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -O2
LDFLAGS = -lm

# Define the source directory
SRC_DIR = src
# Define the results directory (ensure it exists)
RESULTS_DIR = results
# Define the target directory for executables
TARGET_DIR = target

# Source files
GRAPH_SRCS = $(SRC_DIR)/graph.c
DAG_GEN_SRCS = $(SRC_DIR)/dag_generator.c
TOPO_SORT_SRCS = $(SRC_DIR)/topological_sort.c
UNDIR_GEN_SRCS = $(SRC_DIR)/undirected_graph_generator.c
PRIM_MST_SRCS = $(SRC_DIR)/prim_mst.c
PRIM_MST_HEAP_SRCS = $(SRC_DIR)/prim_mst_heap.c


BENCH_TOPO_SRC = $(SRC_DIR)/benchmark_topo_sort.c
BENCH_PRIM_SRC = $(SRC_DIR)/benchmark_prim.c

# Object files will be placed in SRC_DIR for simplicity here, or use a build directory
GRAPH_OBJS = $(GRAPH_SRCS:.c=.o)
DAG_GEN_OBJS = $(DAG_GEN_SRCS:.c=.o)
TOPO_SORT_OBJS = $(TOPO_SORT_SRCS:.c=.o)
UNDIR_GEN_OBJS = $(UNDIR_GEN_SRCS:.c=.o)
PRIM_MST_OBJS = $(PRIM_MST_SRCS:.c=.o)
PRIM_MST_HEAP_OBJS = $(PRIM_MST_HEAP_SRCS:.c=.o)

# Executable names
BENCH_TOPO_EXE = $(TARGET_DIR)/benchmark_topo_sort
BENCH_PRIM_EXE = $(TARGET_DIR)/benchmark_prim

.PHONY: all clean directories

all: directories $(BENCH_TOPO_EXE) $(BENCH_PRIM_EXE)

directories:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(RESULTS_DIR)

# Rule to compile .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/graph.h
	$(CC) $(CFLAGS) -c $< -o $@

# Benchmark for Topological Sort
$(BENCH_TOPO_EXE): $(BENCH_TOPO_SRC) $(GRAPH_OBJS) $(DAG_GEN_OBJS) $(TOPO_SORT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Benchmark for Prim's MST
$(BENCH_PRIM_EXE): $(BENCH_PRIM_SRC) $(GRAPH_OBJS) $(UNDIR_GEN_OBJS) $(PRIM_MST_OBJS) $(PRIM_MST_HEAP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(BENCH_TOPO_EXE) $(BENCH_PRIM_EXE)
	rm -f $(RESULTS_DIR)/*.csv
	# Optionally remove target and results dirs if empty or if you want full clean
	#-rmdir $(TARGET_DIR) 2>/dev/null || true
	#-rmdir $(RESULTS_DIR) 2>/dev/null || true

# Example run commands (manual)
run_topo_benchmark: $(BENCH_TOPO_EXE)
	./$(BENCH_TOPO_EXE)

run_prim_benchmark: $(BENCH_PRIM_EXE)
	./$(BENCH_PRIM_EXE)