#include "render.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define TAILLE_CASE 5
#define LARGEUR_FENETRE (LARGEUR_GRILLE * TAILLE_CASE)
#define HAUTEUR_FENETRE (HAUTEUR_GRILLE * TAILLE_CASE)

static SDL_Window *fenetre = NULL;
static SDL_Renderer *rendu = NULL;

void initialiser_rendu(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return;
    }

    fenetre = SDL_CreateWindow(
        "Splash - Visualisation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE,
        0
    );

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
}

static void couleur_joueur(int id)
{
    switch (id) {
        case 0: SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); break;
        case 1: SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255); break;
        case 2: SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); break;
        case 3: SDL_SetRenderDrawColor(rendu, 255, 255, 0, 255); break;
        default: SDL_SetRenderDrawColor(rendu, 40, 40, 40, 255);
    }
}

void afficher_grille(const Grille *grille)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return;
    }

    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);

    for (int x = 0; x < LARGEUR_GRILLE; x++) {
        for (int y = 0; y < HAUTEUR_GRILLE; y++) {
            couleur_joueur(grille->cases[x][y].proprietaire);

            SDL_Rect rect = {
                x * TAILLE_CASE,
                y * TAILLE_CASE,
                TAILLE_CASE,
                TAILLE_CASE
            };

            SDL_RenderFillRect(rendu, &rect);
        }
    }

    SDL_RenderPresent(rendu);
}

void fermer_rendu(void)
{
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}
