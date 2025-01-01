# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I src/headers
SRC_DIR = src
OBJ_DIR = build
TARGET = app

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Create the target executable
$(TARGET): $(OBJS)
	@echo "Linking executable $(TARGET)..."
	@$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean the build
clean:
	@echo "Cleaning build files..."
	@rm -rf $(OBJ_DIR) $(TARGET)

# Run the application
run: $(TARGET)
	@./$(TARGET)

.PHONY: all clean run
