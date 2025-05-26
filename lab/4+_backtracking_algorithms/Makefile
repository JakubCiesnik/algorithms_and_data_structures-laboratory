CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

# Source files
SOURCES = src/graph.c src/graph_generator.c src/find_euler.c src/find_hamilton.c src/main.c
TARGET = target/main

# Build and run the main program
run: $(TARGET)
	@mkdir -p results
	./$(TARGET)

# Build target
$(TARGET): $(SOURCES) src/graph.h
	@mkdir -p target
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

# Graph visualization
graph:
	python3 graph_visualizer.py

# Generate Plot
plot:
	python3 plot_results.py

# Help target
help:
	@echo "Available targets:"
	@echo "  run              - Build and run the main program"
	@echo "  graph            - Run the graph visualizer (Python)"
	@echo "  plot             - Run the plot generator (Python)"
	@echo "  clean            - Remove all build artifacts"
	@echo "  help             - Show this help message"

# Clean
clean:
	rm -rf target

.PHONY: run graph help clean plot
