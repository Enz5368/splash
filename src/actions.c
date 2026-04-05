#include "actions.h"

int cout_action(char action, int multiplicateur) {
    int base_cost = 1;
    switch (action) {
        case ACTION_STILL:
        case ACTION_MOVE_L: case ACTION_MOVE_R:
        case ACTION_MOVE_U: case ACTION_MOVE_D:
            base_cost = 1; break;
        case ACTION_TELEPORT_L: case ACTION_TELEPORT_R:
        case ACTION_TELEPORT_U: case ACTION_TELEPORT_D:
            base_cost = 2; break;
        case ACTION_BOMB:
            base_cost = 9; break; // 
        case ACTION_DASH_L: case ACTION_DASH_R:
        case ACTION_DASH_U: case ACTION_DASH_D:
            base_cost = 10; break;
        case ACTION_MUTE:
            base_cost = 30; break; // 
        case ACTION_SWAP:
            base_cost = 35; break; // 
        case ACTION_CLEAN:
            base_cost = 40; break; // 
        case ACTION_FORK:
            base_cost = 0; break; // Coût variable à gérer dans l'engine 
        default: base_cost = 1;
    }
    return base_cost * multiplicateur; // Multiplicateur = 2 si clone actif 
}