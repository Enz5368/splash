#include "loader.h"
#include <dlfcn.h>
#include <stdio.h>

int charger_joueur(const char *chemin_bibliotheque, Joueur *joueur)
{
    void *handle = dlopen(chemin_bibliotheque, RTLD_LAZY);
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
