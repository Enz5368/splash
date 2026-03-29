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

    int choix = rand() % 13;

    switch (choix) {
        case 0:  return ACTION_MOVE_L;
        case 1:  return ACTION_MOVE_R;
        case 2:  return ACTION_MOVE_U;
        case 3:  return ACTION_MOVE_D;
        case 4:  return ACTION_DASH_L;
        case 5:  return ACTION_DASH_R;
        case 6:  return ACTION_DASH_U;
        case 7:  return ACTION_DASH_D;
        case 8:  return ACTION_TELEPORT_L;
        case 9:  return ACTION_TELEPORT_R;
        case 10: return ACTION_TELEPORT_U;
        case 11: return ACTION_TELEPORT_D;
        default: return ACTION_STILL;
    }
}