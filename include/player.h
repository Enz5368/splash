#ifndef PLAYER_H
#define PLAYER_H

#include "actions.h"
#include <stdbool.h>

typedef char (*fonction_action_t)(void);

typedef struct {
    int id;
    int x, y;
    int credits;
    int couleur;
    fonction_action_t get_action;

    // --- Addendum : États ---
    int multiplicateur_cout; 
    int timer_mute;          
    int timer_swap;          
    int id_beneficiaire_swap; 

    // --- Addendum : Clone (Fork) ---
    bool fork_en_attente;   
    int fork_delay_timer;    
    int fork_active_timer;   
    int fork_x, fork_y;     

    // --- Addendum : Bombe ---
    bool bombe_posee;       
    int bombe_timer;        
    int bombe_x, bombe_y;    

    // --- Addendum : Fichier Texte ---
    bool is_txt;
    char actions_txt[256];   // Stocke la liste des actions lues 
    int nb_actions_txt;
    int index_action_txt;
    
} Joueur;

#endif