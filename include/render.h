#ifndef RENDER_H
#define RENDER_H

#include "grid.h"
#include "player.h"

/* Initialisation et affichage */
void initialiser_affichage(void);
void afficher_etat(const Grille *grille, Joueur joueurs[], int nombre_joueurs);
void fermer_affichage(void);

#endif
