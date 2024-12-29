CC = gcc
CFLAGS = -std=c99 -I./src -g -Wno-implicit-function-declaration
LDFLAGS = -w -lncurses -lSDL2 -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -Wall -Wextra -Wno-unused-parameter $(CFLAGS) $^ -o $@ $(LDFLAGS)
	cp $(BIN_DIR)/main ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
