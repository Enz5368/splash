#ifndef PLAYER_H
#define PLAYER_H

#include "actions.h"

/* Fonction exportée par les joueurs IA (.so) */
typedef Action (*fonction_action_t)(void);

/* Structure joueur côté moteur */
typedef struct {
    int id;
    int x;
    int y;
    int credits;
    int couleur;

    fonction_action_t get_action;
} Joueur;

#endif
