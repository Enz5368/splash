#ifndef RENDER_H
#define RENDER_H

#include "grid.h"

/* Initialisation SDL */
void initialiser_rendu(void);

/* Affichage de la grille */
void afficher_grille(const Grille *grille);

/* Fermeture SDL */
void fermer_rendu(void);

#endif
