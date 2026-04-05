#include "actions.h"
#include <stdlib.h>
#include <time.h>

char get_action()
{
    static int initialise = 0;
    if (!initialise) {
        srand(time(NULL));
        initialise = 1;
    }

    /* Il y a maintenant 18 actions possibles (de 0 à 17) */
    int choix = rand() % 18;

    switch (choix) {
        case 0:  return ACTION_STILL;
        case 1:  return ACTION_MOVE_L;
        case 2:  return ACTION_MOVE_R;
        case 3:  return ACTION_MOVE_U;
        case 4:  return ACTION_MOVE_D;
        
        case 5:  return ACTION_DASH_L;
        case 6:  return ACTION_DASH_R;
        case 7:  return ACTION_DASH_U;
        case 8:  return ACTION_DASH_D;
        
        case 9:  return ACTION_TELEPORT_L;
        case 10: return ACTION_TELEPORT_R;
        case 11: return ACTION_TELEPORT_U;
        case 12: return ACTION_TELEPORT_D;
        
        /* Les nouvelles actions de l'addendum */
        case 13: return ACTION_BOMB;
        case 14: return ACTION_FORK;
        case 15: return ACTION_CLEAN;
        case 16: return ACTION_MUTE;
        case 17: return ACTION_SWAP;
        
        default: return ACTION_STILL;
    }
}