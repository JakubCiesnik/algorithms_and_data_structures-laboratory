CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -O2
LDFLAGS = -lm

SRC_DIR = src
RESULTS_DIR = results
TARGET_DIR = target

# Ensure target and results directories exist
.PHONY: directories all clean

directories:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(RESULTS_DIR)

all: directories test_graph

test_graph: $(SRC_DIR)/test_graph.c \
           $(SRC_DIR)/def_graph.c \
           $(SRC_DIR)/euler_check.c \
           $(SRC_DIR)/hamilton_check.c \
           $(SRC_DIR)/graph_generator.c
	$(CC) $(CFLAGS) \
	  $(SRC_DIR)/test_graph.c \
	  $(SRC_DIR)/def_graph.c \
	  $(SRC_DIR)/euler_check.c \
	  $(SRC_DIR)/hamilton_check.c \
	  $(SRC_DIR)/graph_generator.c \
	  -o $(TARGET_DIR)/test_graph $(LDFLAGS)

run: all
	./$(TARGET_DIR)/test_graph

clean:
	rm -f $(TARGET_DIR)/test_graph
	rm -f results.csv