#include "actions.h"

int cout_action(char action)
{
    switch (action) {
        case ACTION_MOVE_L:
        case ACTION_MOVE_R:
        case ACTION_MOVE_U:
        case ACTION_MOVE_D:
            return 1; // 

        case ACTION_DASH_L:
        case ACTION_DASH_R:
        case ACTION_DASH_U:
        case ACTION_DASH_D:
            return 10; // 

        case ACTION_TELEPORT_L:
        case ACTION_TELEPORT_R:
        case ACTION_TELEPORT_U:
        case ACTION_TELEPORT_D:
            return 2; // 

        case ACTION_STILL:
        default:
            return 1; // 
    }
}