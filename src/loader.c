#include "loader.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Convertit la chaîne de caractères en code Action */
static char string_to_action(const char* str) {
    if (strstr(str, "ACTION_MOVE_L")) return ACTION_MOVE_L;
    if (strstr(str, "ACTION_MOVE_R")) return ACTION_MOVE_R;
    if (strstr(str, "ACTION_MOVE_U")) return ACTION_MOVE_U;
    if (strstr(str, "ACTION_MOVE_D")) return ACTION_MOVE_D;
    
    if (strstr(str, "ACTION_DASH_L")) return ACTION_DASH_L;
    if (strstr(str, "ACTION_DASH_R")) return ACTION_DASH_R;
    if (strstr(str, "ACTION_DASH_U")) return ACTION_DASH_U;
    if (strstr(str, "ACTION_DASH_D")) return ACTION_DASH_D;
    
    if (strstr(str, "ACTION_TELEPORT_L")) return ACTION_TELEPORT_L;
    if (strstr(str, "ACTION_TELEPORT_R")) return ACTION_TELEPORT_R;
    if (strstr(str, "ACTION_TELEPORT_U")) return ACTION_TELEPORT_U;
    if (strstr(str, "ACTION_TELEPORT_D")) return ACTION_TELEPORT_D;
    
    if (strstr(str, "ACTION_BOMB")) return ACTION_BOMB;
    if (strstr(str, "ACTION_FORK")) return ACTION_FORK;
    if (strstr(str, "ACTION_CLEAN")) return ACTION_CLEAN;
    if (strstr(str, "ACTION_MUTE")) return ACTION_MUTE;
    if (strstr(str, "ACTION_SWAP")) return ACTION_SWAP;

    return ACTION_STILL;
}

int charger_joueur(const char *chemin, Joueur *joueur)
{
    joueur->is_txt = false;
    joueur->nb_actions_txt = 0;
    joueur->index_action_txt = 0;

    /* 1. Détection si le fichier est un .txt */
    if (strstr(chemin, ".txt")) {
        FILE *f = fopen(chemin, "r");
        if (!f) {
            fprintf(stderr, "Erreur lecture fichier texte: %s\n", chemin);
            return -1;
        }
        
        char buffer[1024];
        /* On lit toutes les lignes du fichier au cas où il y a des sauts de ligne */
        while (fgets(buffer, sizeof(buffer), f)) {
            char *token = strtok(buffer, ", \n\r\t");
            while (token != NULL && joueur->nb_actions_txt < 256) {
                joueur->actions_txt[joueur->nb_actions_txt] = string_to_action(token);
                joueur->nb_actions_txt++;
                token = strtok(NULL, ", \n\r\t");
            }
        }
        fclose(f);
        joueur->is_txt = true;
        return 0; /* Chargement texte réussi */
    }

    /* 2. Chargement classique pour les .so */
    void *handle = dlopen(chemin, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Erreur dlopen: %s\n", dlerror());
        return -1;
    }

    joueur->get_action = (fonction_action_t)dlsym(handle, "get_action");
    if (!joueur->get_action) {
        fprintf(stderr, "Erreur dlsym: %s\n", dlerror());
        return -1;
    }

    return 0;
}