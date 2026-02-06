# =========================
# Projet Splash – S6
# =========================

# Compilateur
CC = gcc

# Options de compilation
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -ldl

# Dossiers
SRC_DIR    = src
INC_DIR    = include
PLAYER_DIR = players

# Exécutable
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
# Joueurs IA
# =========================
PLAYER_SRC = \
	$(PLAYER_DIR)/random_player.c

PLAYER_SO = \
	$(PLAYER_DIR)/random_player.so

# =========================
# Règles principales
# =========================

all: $(TARGET) players

# Exécutable principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Joueurs (.so)
# =========================

players: $(PLAYER_DIR) $(PLAYER_SO)

# Crée le dossier players si absent
$(PLAYER_DIR):
	mkdir -p $(PLAYER_DIR)

# Compilation d'un joueur IA
$(PLAYER_DIR)/%.so: $(PLAYER_DIR)/%.c $(INC_DIR)/actions.h
	$(CC) -Wall -Wextra -std=c11 -fPIC -shared -I$(INC_DIR) -o $@ $<

# =========================
# Nettoyage
# =========================

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)
	rm -f $(PLAYER_DIR)/*.so

re: fclean all

# =========================
# Phony
# =========================
.PHONY: all clean fclean re players
