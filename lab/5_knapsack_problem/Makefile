# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -g -Iinclude
LDFLAGS := 

# Directory structure
SRC_DIR := src
TARGET_DIR := target
BUILD_DIR := $(TARGET_DIR)/build

# Source files (auto-discovered)
SRCS := $(wildcard $(SRC_DIR)/*.c)
# Targets to build (without .c extension)
TARGETS := dataset_generator main

# Object files (in build directory)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
# Executables (in target directory)
EXECS := $(addprefix $(TARGET_DIR)/,$(TARGETS))

.PHONY: all clean

all: $(EXECS) | $(TARGET_DIR)

# Special rule for main: requires main.o AND io_util.o
$(TARGET_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/io_util.o | $(TARGET_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET_DIR)/dataset_generator: $(BUILD_DIR)/dataset_generator.o $(BUILD_DIR)/io_util.o | $(TARGET_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# General rule for other executables
$(TARGET_DIR)/%: $(BUILD_DIR)/%.o | $(TARGET_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Compile C sources with dependency generation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	@cp $(BUILD_DIR)/$*.d $(BUILD_DIR)/$*.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	      -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_DIR)/$*.d >> $(BUILD_DIR)/$*.P; \
	  rm -f $(BUILD_DIR)/$*.d

# Create directories
$(TARGET_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(TARGET_DIR)

# Auto-generated dependencies (adds .d files)
DEPFILES := $(OBJS:.o=.d)
-include $(DEPFILES)
