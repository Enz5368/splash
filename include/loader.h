#ifndef LOADER_H
#define LOADER_H

#include "player.h"

/* Charge une bibliothèque joueur et récupère get_action */
int charger_joueur(const char *chemin_bibliotheque, Joueur *joueur);

#endif
