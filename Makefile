# =========================
# Projet Splash – S6
# =========================

CC = gcc

CFLAGS   = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS  = -ldl
SDLFLAGS = $(shell sdl2-config --cflags --libs)

SRC_DIR    = src
INC_DIR    = include
PLAYER_DIR = players

TARGET = splash

# =========================
# Sources moteur
# =========================

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/engine.c \
	$(SRC_DIR)/actions.c \
	$(SRC_DIR)/grid.c \
	$(SRC_DIR)/loader.c \
	$(SRC_DIR)/render.c

OBJ = $(SRC:.c=.o)

# =========================
# Joueurs IA (4 fichiers distincts)
# =========================

PLAYER_SRC = \
	$(PLAYER_DIR)/random_player1.c \
	$(PLAYER_DIR)/random_player2.c \
	$(PLAYER_DIR)/random_player3.c \
	$(PLAYER_DIR)/random_player4.c

PLAYER_SO = \
	$(PLAYER_DIR)/random_player1.so \
	$(PLAYER_DIR)/random_player2.so \
	$(PLAYER_DIR)/random_player3.so \
	$(PLAYER_DIR)/random_player4.so

# =========================
# Règles principales
# =========================

all: $(TARGET) players

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Joueurs IA (.so)
# =========================

players: $(PLAYER_DIR) $(PLAYER_SO)

$(PLAYER_DIR):
	mkdir -p $(PLAYER_DIR)

$(PLAYER_DIR)/%.so: $(PLAYER_DIR)/%.c include/actions.h
	$(CC) -Wall -Wextra -std=c11 -fPIC -shared -Iinclude -o $@ $<

# =========================
# Nettoyage
# =========================

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)
	rm -f $(PLAYER_DIR)/*.so

re: fclean all

.PHONY: all clean fclean re players
