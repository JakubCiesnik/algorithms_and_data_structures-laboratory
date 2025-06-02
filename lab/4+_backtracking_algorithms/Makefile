CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

# Common source files
COMMON_SRCS = src/graph.c src/graph_generator.c src/find_euler.c src/find_hamilton.c
MAIN_SRCS = src/main1.c src/main2.c src/main_code_review.c
TARGETS = $(patsubst src/%.c, target/%, $(MAIN_SRCS))

# Build all targets
all: $(TARGETS)

# Run targets
run: run_main1 run_main2 run_main_code_review

run_main1: target/main1
	@mkdir -p results
	./target/main1

run_main2: target/main2
	@mkdir -p results
	./target/main2

run_main_code_review: target/main_code_review
	@mkdir -p results
	./target/main_code_review

# Pattern rule to build each target
target/%: src/%.c $(COMMON_SRCS) src/graph.h
	@mkdir -p target
	$(CC) $(CFLAGS) $< $(COMMON_SRCS) -o $@ $(LDFLAGS)

# Graph visualization
graph:
	python3 graph_visualizer.py

# Generate Plot
plot:
	python3 plot_results.py

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build all main programs"
	@echo "  run              - Run all main programs (main1, main2, main_code_review)"
	@echo "  run_main1        - Build and run main1"
	@echo "  run_main2        - Build and run main2"
	@echo "  run_main_code_review - Build and run main_code_review"
	@echo "  graph            - Run the graph visualizer (Python)"
	@echo "  plot             - Run the plot generator (Python)"
	@echo "  clean            - Remove all build artifacts"
	@echo "  help             - Show this help message"

# Clean
clean:
	rm -rf target

.PHONY: all run run_main1 run_main2 run_main_code_review graph plot help clean
