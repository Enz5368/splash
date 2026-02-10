#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <stdbool.h>

/* États du menu */
typedef enum {
    MENU_PRINCIPAL,
    MENU_REGLES
} MenuState;

/* Résultat du menu */
typedef enum {
    MENU_START,
    MENU_QUIT
} MenuResult;

/* Lance le menu */
MenuResult lancer_menu(SDL_Renderer *renderer);

#endif
