#ifndef ACTIONS_H
#define ACTIONS_H

/* Codes des actions possibles */
typedef enum {
    ACTION_DEPLACER_GAUCHE,
    ACTION_DEPLACER_DROITE,
    ACTION_DEPLACER_HAUT,
    ACTION_DEPLACER_BAS,

    ACTION_DASH_GAUCHE,
    ACTION_DASH_DROITE,
    ACTION_DASH_HAUT,
    ACTION_DASH_BAS,

    ACTION_TELEPORT_GAUCHE,
    ACTION_TELEPORT_DROITE,
    ACTION_TELEPORT_HAUT,
    ACTION_TELEPORT_BAS,

    ACTION_IMMOBILE
} Action;

/* Coût d'une action en crédits */
int cout_action(Action action);

#endif
