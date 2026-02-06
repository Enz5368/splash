#include "actions.h"
#include <stdlib.h>
#include <time.h>

/*
 * Joueur IA aléatoire
 * Retourne une action valide à chaque appel
 */

Action get_action(void)
{
    static int initialise = 0;

    if (!initialise) {
        srand(time(NULL));
        initialise = 1;
    }

    int choix = rand() % 13;

    switch (choix) {
        case 0:  return ACTION_DEPLACER_GAUCHE;
        case 1:  return ACTION_DEPLACER_DROITE;
        case 2:  return ACTION_DEPLACER_HAUT;
        case 3:  return ACTION_DEPLACER_BAS;

        case 4:  return ACTION_DASH_GAUCHE;
        case 5:  return ACTION_DASH_DROITE;
        case 6:  return ACTION_DASH_HAUT;
        case 7:  return ACTION_DASH_BAS;

        case 8:  return ACTION_TELEPORT_GAUCHE;
        case 9:  return ACTION_TELEPORT_DROITE;
        case 10: return ACTION_TELEPORT_HAUT;
        case 11: return ACTION_TELEPORT_BAS;

        default:
            return ACTION_IMMOBILE;
    }
}
