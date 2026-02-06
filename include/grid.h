#ifndef GRID_H
#define GRID_H

#define LARGEUR_GRILLE 100
#define HAUTEUR_GRILLE 100

/* Une case du plateau */
typedef struct {
    int proprietaire; /* -1 si libre, sinon id du joueur */
} Case;

/* La grille complète */
typedef struct {
    Case cases[LARGEUR_GRILLE][HAUTEUR_GRILLE];
} Grille;

/* Fonctions de gestion de la grille */
void initialiser_grille(Grille *grille);
void marquer_case(Grille *grille, int x, int y, int id_joueur);

#endif
