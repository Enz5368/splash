#include "engine.h"
#include "loader.h"
#include "menu.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s joueur1.so joueur2.so ...\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Splash - Menu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    MenuResult choix = lancer_menu(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if (choix != MENU_START) {
        SDL_Quit();
        return 0;
    }

    /* Initialisation joueurs */
    int nombre_joueurs = argc - 1;
    Joueur joueurs[MAX_JOUEURS];

    /* 1. ON NETTOIE LA MÉMOIRE (Évite les bugs de timers et bombes fantômes) */
    memset(joueurs, 0, sizeof(joueurs));

    for (int i = 0; i < nombre_joueurs; i++) {
        joueurs[i].id = i;
        joueurs[i].x = i * 10;
        joueurs[i].y = i * 10;
        joueurs[i].credits = CREDITS_INITIAUX;
        joueurs[i].couleur = i;
        
        /* 2. ON INITIALISE LE MULTIPLICATEUR A 1 (Sinon les coups sont gratuits !) */
        joueurs[i].multiplicateur_cout = 1;

        if (charger_joueur(argv[i + 1], &joueurs[i]) != 0) {
            fprintf(stderr, "Erreur chargement joueur %d\n", i);
            SDL_Quit();
            return 1;
        }
    }

    lancer_partie(joueurs, nombre_joueurs);

    SDL_Quit();
    return 0;
}