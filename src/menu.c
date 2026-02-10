#include "menu.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

/* ---------- OUTILS ---------- */

bool bouton_clique(SDL_Rect btn, int x, int y)
{
    return (x >= btn.x && x <= btn.x + btn.w &&
            y >= btn.y && y <= btn.y + btn.h);
}

void draw_text(SDL_Renderer *renderer, TTF_Font *font,
               const char *text, SDL_Color color,
               int x, int y)
{
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void draw_button(SDL_Renderer *renderer, TTF_Font *font,
                 SDL_Rect btn, const char *label)
{
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &btn);

    int text_x = btn.x + btn.w / 2 - (strlen(label) * 8);
    int text_y = btn.y + btn.h / 2 - 10;

    draw_text(renderer, font, label, textColor, text_x, text_y);
}

/* ---------- MENU ---------- */

MenuResult lancer_menu(SDL_Renderer *renderer)
{
    SDL_Event e;
    MenuState etat = MENU_PRINCIPAL;

    /* Boutons */
    SDL_Rect btn_start  = {300, 220, 200, 50};
    SDL_Rect btn_regles = {300, 290, 200, 50};
    SDL_Rect btn_quit   = {300, 360, 200, 50};
    SDL_Rect btn_retour = {300, 470, 200, 40};

    /* Init TTF */
    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init\n");
        return MENU_QUIT;
    }

    TTF_Font *font = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20);

    if (!font) {
        printf("Erreur chargement police\n");
        return MENU_QUIT;
    }

    while (1) {
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                return MENU_QUIT;

            /* ===== MENU PRINCIPAL ===== */
            if (etat == MENU_PRINCIPAL && e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (bouton_clique(btn_start, x, y))
                    return MENU_START;

                if (bouton_clique(btn_regles, x, y))
                    etat = MENU_REGLES;

                if (bouton_clique(btn_quit, x, y))
                    return MENU_QUIT;
            }

            /* ===== MENU REGLES ===== */
            if (etat == MENU_REGLES) {
                if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_ESCAPE)
                    etat = MENU_PRINCIPAL;

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int x = e.button.x;
                    int y = e.button.y;

                    if (bouton_clique(btn_retour, x, y))
                        etat = MENU_PRINCIPAL;
                }
            }
        }

        /* ===== RENDU ===== */
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (etat == MENU_PRINCIPAL) {
            draw_button(renderer, font, btn_start,  "START");
            draw_button(renderer, font, btn_regles, "REGLES");
            draw_button(renderer, font, btn_quit,   "QUIT");
        }

        if (etat == MENU_REGLES) {
            SDL_Rect panel = {150, 120, 500, 320};
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
            SDL_RenderFillRect(renderer, &panel);

            SDL_Color white = {255, 255, 255, 255};

            draw_text(renderer, font, "REGLES DU JEU SPLASH", white, 200, 140);
            draw_text(renderer, font, "- Chaque joueur commence avec des credits", white, 180, 190);
            draw_text(renderer, font, "- Une action coute des credits", white, 180, 220);
            draw_text(renderer, font, "- Les joueurs jouent a tour de role", white, 180, 250);
            draw_text(renderer, font, "- Le but est de controler la grille", white, 180, 280);
            draw_text(renderer, font, "- Fin quand plus aucun coup possible", white, 180, 310);

            draw_button(renderer, font, btn_retour, "ESC");
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
