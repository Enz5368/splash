#ifndef ACTIONS_H
#define ACTIONS_H

/* * Utilisation des noms exacts du sujet 
 * On définit des valeurs numériques explicites pour assurer la compatibilité 
 */
typedef enum {
    ACTION_MOVE_L = 0,
    ACTION_MOVE_R,
    ACTION_MOVE_U,
    ACTION_MOVE_D,

    ACTION_DASH_L,
    ACTION_DASH_R,
    ACTION_DASH_U,
    ACTION_DASH_D,

    ACTION_TELEPORT_L,
    ACTION_TELEPORT_R,
    ACTION_TELEPORT_U,
    ACTION_TELEPORT_D,

    ACTION_STILL
} Action;

/* Coût d'une action en crédits  */
int cout_action(char action);

#endif