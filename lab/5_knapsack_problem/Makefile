# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -g -Iinclude
LDFLAGS := 

# Directory structure
SRC_DIR := src
TARGET_DIR := target

# Targets to build
TARGETS := main dataset_generator benchmark

# Executables (in target directory)
EXECS := $(addprefix $(TARGET_DIR)/,$(TARGETS))

.PHONY: all clean

all: $(EXECS) | $(TARGET_DIR)

# Rule for main
$(TARGET_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/io_util.c $(SRC_DIR)/greedy.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for dataset_generator
$(TARGET_DIR)/dataset_generator: $(SRC_DIR)/dataset_generator.c $(SRC_DIR)/io_util.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# rule for benchmark
$(TARGET_DIR)/benchmark: $(SRC_DIR)/benchmark.c $(SRC_DIR)/io_util.c $(SRC_DIR)/greedy.c | $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Create target directory
$(TARGET_DIR):
	mkdir -p $@

clean:
	rm -rf $(TARGET_DIR)
