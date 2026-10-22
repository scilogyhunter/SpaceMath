# Makefile for spacemath library
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./src
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR = src
OBJ_DIR = out/obj
LIB_DIR = out
BIN_DIR = out

# Source files for library
LIB_SRCS  = $(SRC_DIR)/others.c 
LIB_SRCS += $(SRC_DIR)/matrix.c 
LIB_SRCS += $(SRC_DIR)/quat.c 
LIB_SRCS += $(SRC_DIR)/vector.c 
LIB_SRCS += $(SRC_DIR)/rotation.c 
LIB_SRCS += $(SRC_DIR)/axis.c
LIB_SRCS += $(SRC_DIR)/eula.c


LIB_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

# Directories
TEST_SRC_DIR = test
TEST_OBJ_DIR = out/obj
TEST_BIN_DIR = out

# Source files for test programs
TEST_SRC  = $(TEST_SRC_DIR)/test_main.c
TEST_SRC += $(TEST_SRC_DIR)/test_others.c
TEST_SRC += $(TEST_SRC_DIR)/test_vector.c
TEST_SRC += $(TEST_SRC_DIR)/test_quat.c
TEST_SRC += $(TEST_SRC_DIR)/test_matrix.c
TEST_SRC += $(TEST_SRC_DIR)/test_rotation.c
TEST_SRC += $(TEST_SRC_DIR)/test_random.c
TEST_SRC += $(TEST_SRC_DIR)/test_eula.c
TEST_SRC += $(TEST_SRC_DIR)/test_axis.c


TEST_OBJS = $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))

# Main test executable
TEST_MAIN = $(TEST_BIN_DIR)/test

# Library name
LIB_NAME = libspacemath.a
LIB = $(LIB_DIR)/$(LIB_NAME)

# Default target
all: $(LIB) $(TEST_MAIN)

# Create static library
$(LIB): $(LIB_OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Create main test executable (links all test object files)
$(TEST_MAIN): $(TEST_OBJS) $(LIB) | $(BIN_DIR)
	$(CC) -o $@ $(TEST_OBJS) -L$(LIB_DIR) -lspacemath -lm -lquadmath

# Compile library object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test object files
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(OBJ_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

# Clean target
clean:
	rm -rf out

# Phony targets
.PHONY: all clean
