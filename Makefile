# =========================
# Projet Splash – S6
# =========================

# Compilateur et options
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -ldl

# Dossiers
SRC_DIR     = src
PLAYER_DIR  = players
BUILD_DIR   = build

# Exécutable
TARGET = splash

# Fichiers source moteur
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/engine.c \
	$(SRC_DIR)/actions.c \
	$(SRC_DIR)/grid.c \
	$(SRC_DIR)/loader.c \
	$(SRC_DIR)/render.c 

# Objets
OBJ = $(SRC:.c=.o)

# Joueurs IA (bibliothèques dynamiques)
PLAYERS = \
	$(PLAYER_DIR)/random_player.so

# =========================
# Règles principales
# =========================

all: $(TARGET) players

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Joueurs IA (.so)
# =========================

players: $(PLAYERS)

$(PLAYER_DIR)/%.so: $(PLAYER_DIR)/%.c include/actions.h
	$(CC) -Wall -Wextra -std=c11 -fPIC -shared -o $@ $<

# =========================
# Nettoyage
# =========================

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET) $(PLAYER_DIR)/*.so

re: fclean all

# =========================
# Phony
# =========================

.PHONY: all clean fclean re players
