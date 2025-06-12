
# Top-level Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -I. -Ishell -Iparser -Isrc -Isrc/shell -Isrc/parser

# Build directories
PARSER_DIR = parser
SHELL_DIR = shell
BUILD_DIR = build

# Object files
OBJS = $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/parser.o $(BUILD_DIR)/lexer.o \
       $(BUILD_DIR)/shell.o $(BUILD_DIR)/alias.o \
       $(BUILD_DIR)/execution.o $(BUILD_DIR)/shell_ast.o \
       $(BUILD_DIR)/shell_utils.o

TARGET = $(BUILD_DIR)/lshell

.PHONY: all clean submodules

all: $(BUILD_DIR) submodules $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build submodules
submodules:
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(SHELL_DIR)
	cp $(PARSER_DIR)/build/*.o $(BUILD_DIR)/
	cp $(SHELL_DIR)/build/*.o $(BUILD_DIR)/

# Compile main.c
$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $@

# Link all object files into final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lreadline

# Clean up everything
clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(SHELL_DIR) clean

