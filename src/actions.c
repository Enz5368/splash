#include "actions.h"

/* Retourne le coût d'une action */
int cout_action(Action action)
{
    switch (action) {
        case ACTION_DEPLACER_GAUCHE:
        case ACTION_DEPLACER_DROITE:
        case ACTION_DEPLACER_HAUT:
        case ACTION_DEPLACER_BAS:
            return 1;

        case ACTION_DASH_GAUCHE:
        case ACTION_DASH_DROITE:
        case ACTION_DASH_HAUT:
        case ACTION_DASH_BAS:
            return 10;

        case ACTION_TELEPORT_GAUCHE:
        case ACTION_TELEPORT_DROITE:
        case ACTION_TELEPORT_HAUT:
        case ACTION_TELEPORT_BAS:
            return 2;

        case ACTION_IMMOBILE:
        default:
            return 1;
    }
}
