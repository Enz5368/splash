#ifndef ACTIONS_H
#define ACTIONS_H

typedef enum {
    ACTION_STILL = 0,    
    ACTION_MOVE_L,       
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
    ACTION_BOMB,         
    ACTION_FORK,         
    ACTION_CLEAN,       
    ACTION_MUTE,         
    ACTION_SWAP,         
    ACTION_NUMBER        
} Action;

int cout_action(char action, int multiplicateur);

#endif