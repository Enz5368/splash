CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -ldl -lSDL2 -lSDL2_ttf

SRC_DIR = src
OBJ_DIR = src

SRCS = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/engine.c \
    $(SRC_DIR)/actions.c \
    $(SRC_DIR)/grid.c \
    $(SRC_DIR)/loader.c \
    $(SRC_DIR)/render.c \
    $(SRC_DIR)/menu.c

OBJS = $(SRCS:.c=.o)

TARGET = splash

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
