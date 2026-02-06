#include "grid.h"

/* Initialise la grille : toutes les cases sont libres */
void initialiser_grille(Grille *grille)
{
    for (int x = 0; x < LARGEUR_GRILLE; x++) {
        for (int y = 0; y < HAUTEUR_GRILLE; y++) {
            grille->cases[x][y].proprietaire = -1;
        }
    }
}

/* Marque une case comme appartenant à un joueur */
void marquer_case(Grille *grille, int x, int y, int id_joueur)
{
    if (x < 0 || x >= LARGEUR_GRILLE || y < 0 || y >= HAUTEUR_GRILLE)
        return;

    grille->cases[x][y].proprietaire = id_joueur;
}
