# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -g -Iinclude
LDFLAGS := 

# Directory structure
SRC_DIR := src
TARGET_DIR := target

# Targets to build
TARGETS := verify dataset_generator benchmark

# Executables (in target directory)
EXECS := $(addprefix $(TARGET_DIR)/,$(TARGETS))

.PHONY: all clean run help debug verify

help:
	@echo "========================================"
	@echo "     Task 5 - Knapsack Problem V2.1     "
	@echo "========================================"
	@echo ""
	@echo "  verify <file>          - Build and run verify.c with custom input file"
	@echo "  benchmark              - Build and run benchmark on all datasets"
	@echo "  clean                  - Remove all build artifacts"
	@echo "  debug                  - Show VS Code debugger info for main"
	@echo "  help                   - Show this help message"
	@echo ""
	@echo "Usage: make verify FILE=plecak.txt > verification_output.txt"

all: $(EXECS) | $(TARGET_DIR)

# Rule for verify
$(TARGET_DIR)/verify: $(SRC_DIR)/verify.c $(SRC_DIR)/io_util.c $(SRC_DIR)/greedy.c $(SRC_DIR)/dynamic.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for dataset_generator
$(TARGET_DIR)/dataset_generator: $(SRC_DIR)/dataset_generator.c $(SRC_DIR)/io_util.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# rule for benchmark
$(TARGET_DIR)/benchmark: $(SRC_DIR)/benchmark.c $(SRC_DIR)/io_util.c $(SRC_DIR)/greedy.c $(SRC_DIR)/dynamic.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Create target directory
$(TARGET_DIR):
	mkdir -p $@

clean:
	rm -rf $(TARGET_DIR)

verify: $(TARGET_DIR)/verify
	@if [ -z "$(FILE)" ]; then \
		echo "\nError: Please specify input file with FILE=filename"; \
		echo "Usage: make verify FILE=your_file.txt"; \
		exit 1; \
	fi
	./$(TARGET_DIR)/verify $(FILE) verify_output.txt

benchmark: $(TARGET_DIR)/benchmark
	@echo "Running benchmark on all datasets..."
	./$(TARGET_DIR)/benchmark
	@echo "Benchmark complete! Results saved to benchmark_results.csv"

debug:
	@echo ""
	@echo "Please use VSC with run & debug predefined tasks to debug"
	@echo ""