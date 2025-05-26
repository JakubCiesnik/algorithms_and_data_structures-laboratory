CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm
SRCDIR = src
TARGETDIR = target
RESULTSDIR = results

# Object files
OBJS = $(TARGETDIR)/graph.o $(TARGETDIR)/graph_generator.o $(TARGETDIR)/algorithms.o

# Create directories
$(shell mkdir -p $(TARGETDIR) $(RESULTSDIR))

# Main targets
all: $(TARGETDIR)/main $(TARGETDIR)/debug

$(TARGETDIR)/main: $(OBJS) $(TARGETDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGETDIR)/debug: $(OBJS) $(TARGETDIR)/debug.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Object file rules
$(TARGETDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/graph.h
	$(CC) $(CFLAGS) -c $< -o $@

# Run targets
run: $(TARGETDIR)/main
	cd $(TARGETDIR) && ./main

debug: $(TARGETDIR)/debug
	cd $(TARGETDIR) && ./debug

# Clean
clean:
	rm -rf $(TARGETDIR)/*.o $(TARGETDIR)/main $(TARGETDIR)/debug

.PHONY: all run debug clean
