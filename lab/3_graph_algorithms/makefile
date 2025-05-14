CC     = gcc
CFLAGS = -O3 -std=c99 -Wall -Wextra -Isrc
SRC    = src
DATA   = dataset
RESULT = results
TGT    = target

all: dirs $(TGT)/daggen $(TGT)/mstgen $(TGT)/benchmark

dirs:
	mkdir -p $(TGT) $(DATA) $(RESULT)

$(TGT)/daggen: $(SRC)/daggen.c $(SRC)/dag.c $(SRC)/graph_utils.c \
               $(SRC)/dag.h $(SRC)/graph_utils.h
	$(CC) $(CFLAGS) $^ -o $@

$(TGT)/mstgen: $(SRC)/mstgen.c $(SRC)/mst.c $(SRC)/graph_utils.c \
               $(SRC)/mst.h $(SRC)/graph_utils.h
	$(CC) $(CFLAGS) $^ -o $@

$(TGT)/benchmark: $(SRC)/benchmark.c \
                  $(SRC)/dag.c $(SRC)/mst.c $(SRC)/graph_utils.c \
                  $(SRC)/dag.h $(SRC)/mst.h $(SRC)/graph_utils.h
	$(CC) $(CFLAGS) $^ -o $@ -lrt

.PHONY: clean generate benchmark

generate: all
	$(TGT)/daggen
	$(TGT)/mstgen

benchmark: generate
	$(TGT)/benchmark

clean:
	rm -rf $(TGT) $(DATA) $(RESULT)
