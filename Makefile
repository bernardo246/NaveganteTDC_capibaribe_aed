# Makefile - Compilacao automatica do Navegador Capibaribe (Dev 5)

CC      = gcc

OS := $(shell uname)

ifeq ($(OS), Darwin)
    # macOS
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
else
    # Linux
    RAYLIB_CFLAGS = -I/usr/local/include
    RAYLIB_LIBS   = -L/usr/local/lib -lraylib -lm -lpthread -ldl -lX11
endif

CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -Ilib -Isrc $(RAYLIB_CFLAGS)
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = build

ALL_SRCS = $(sort $(shell find $(SRC_DIR) $(LIB_DIR) -type f -name '*.c' ! -name 'test_*.c'))
OBJS     = $(patsubst %.c,$(OBJ_DIR)/%.o,$(ALL_SRCS))

TARGET = navegador-capibaribe

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_LIBS) -lcurl -lcjson

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

test_hitbox_obstaculo: src/test_hitbox_obstaculo.c
	$(CC) $(CFLAGS) src/test_hitbox_obstaculo.c -o test_hitbox_obstaculo $(RAYLIB_LIBS)