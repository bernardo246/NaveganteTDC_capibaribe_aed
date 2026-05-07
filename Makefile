# Makefile - Compilacao automatica do Navegador Capibaribe (Dev 5)

CC      = gcc

BREW_PREFIX   := $(shell brew --prefix 2>/dev/null)
RAYLIB_PREFIX := $(shell brew --prefix raylib 2>/dev/null)

RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null)

ifeq ($(strip $(RAYLIB_CFLAGS)),)
RAYLIB_CFLAGS = -I$(RAYLIB_PREFIX)/include -I$(BREW_PREFIX)/include
endif

ifeq ($(strip $(RAYLIB_LIBS)),)
RAYLIB_LIBS = -L$(RAYLIB_PREFIX)/lib -L$(BREW_PREFIX)/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -Ilib -Isrc $(RAYLIB_CFLAGS)
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
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
