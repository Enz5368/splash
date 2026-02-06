#include "grid.h"
#include <stdio.h>

void initialiser_grille(Grille *grille)
{
    for (int x = 0; x < LARGEUR_GRILLE; x++) {
        for (int y = 0; y < HAUTEUR_GRILLE; y++) {
            grille->cases[x][y].proprietaire = -1;
        }
    }
}

void marquer_case(Grille *grille, int x, int y, int id_joueur)
{
    if (x < 0 || x >= LARGEUR_GRILLE || y < 0 || y >= HAUTEUR_GRILLE)
        return;

    grille->cases[x][y].proprietaire = id_joueur;
}

int compter_cases_joueur(const Grille *grille, int id_joueur)
{
    int compteur = 0;

    for (int x = 0; x < LARGEUR_GRILLE; x++) {
        for (int y = 0; y < HAUTEUR_GRILLE; y++) {
            if (grille->cases[x][y].proprietaire == id_joueur) {
                compteur++;
            }
        }
    }

    return compteur;
}

void afficher_scores(const Grille *grille, int nombre_joueurs)
{
    printf("\n===== SCORES FINAUX =====\n");

    for (int i = 0; i < nombre_joueurs; i++) {
        int score = compter_cases_joueur(grille, i);
        printf("Joueur %d : %d cases\n", i, score);
    }
}
