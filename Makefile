# Makefile - Compilacao automatica do Navegador Capibaribe (Dev 5)

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -Ilib -Isrc
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = build

SRC_SRCS = $(wildcard $(SRC_DIR)/*.c)
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
ALL_SRCS = $(SRC_SRCS) $(LIB_SRCS)
OBJS     = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(ALL_SRCS)))

TARGET = navegador-capibaribe

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
