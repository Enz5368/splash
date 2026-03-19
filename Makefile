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

# --- Gestion des joueurs ---
PLAYER_SRCS = $(wildcard players/*.c)
PLAYER_SOS = $(PLAYER_SRCS:.c=.so)

# On ajoute $(PLAYER_SOS) ici pour que 'make' compile tout par défaut
all: $(TARGET) $(PLAYER_SOS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règle pour compiler les .so des joueurs
players/%.so: players/%.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET) players/*.so