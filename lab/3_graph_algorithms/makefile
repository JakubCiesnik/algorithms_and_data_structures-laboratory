# Makefile for Graph Algorithms Benchmark

CC        := gcc
CFLAGS    := -O3 -Wall -Wextra
SRCDIR    := src
TARGETDIR := target
DATADIR   := dataset
RESDIR    := results

DAGGEN    := $(TARGETDIR)/daggen
MSTGEN    := $(TARGETDIR)/mstgen
BENCH     := $(TARGETDIR)/benchmark

# Source files
DAG_SRC   := $(SRCDIR)/dag.c
DAGGEN_SRC:= $(SRCDIR)/daggen.c
MST_SRC   := $(SRCDIR)/mst.c
MSTGEN_SRC:= $(SRCDIR)/mstgen.c
BENCH_SRC := $(SRCDIR)/benchmark.c

.PHONY: all clean dirs

all: dirs $(DAGGEN) $(MSTGEN) $(BENCH)

dirs:
	@mkdir -p $(TARGETDIR) $(DATADIR) $(RESDIR)

# Build daggen (generates DAG datasets)
$(DAGGEN): $(DAGGEN_SRC) $(DAG_SRC)
	$(CC) $(CFLAGS) -o $@ $(DAGGEN_SRC) $(DAG_SRC) -lm

# Build mstgen (generates MST datasets)
$(MSTGEN): $(MSTGEN_SRC) $(MST_SRC) $(DAG_SRC)
	$(CC) $(CFLAGS) -o $@ $(MSTGEN_SRC) $(MST_SRC) $(DAG_SRC) -lm

# Build benchmark (runs all benchmarks)
$(BENCH): $(BENCH_SRC) $(DAG_SRC) $(MST_SRC)
	$(CC) $(CFLAGS) -o $@ $(BENCH_SRC) $(DAG_SRC) $(MST_SRC) -lm

# Clean binaries and results
clean:
	rm -rf $(TARGETDIR)/*
	rm -rf $(DATADIR)/*.txt
	rm -rf $(RESDIR)/*.csv

