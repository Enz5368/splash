#ifndef PLAYER_H
#define PLAYER_H

#include "actions.h"

/* Correction : Le sujet impose char comme type de retour */
typedef char (*fonction_action_t)(void);

typedef struct {
    int id;
    int x;
    int y;
    int credits; // Doit être initialisé à 9000 
    int couleur;

    fonction_action_t get_action;
} Joueur;

#endif