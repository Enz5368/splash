#include "engine.h"
#include "loader.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s joueur1.so joueur2.so ...\n", argv[0]);
        return 1;
    }

    int nombre_joueurs = argc - 1;
    Joueur joueurs[MAX_JOUEURS];

    for (int i = 0; i < nombre_joueurs; i++) {
        joueurs[i].id = i;
        joueurs[i].x = i * 10;
        joueurs[i].y = i * 10;
        joueurs[i].credits = CREDITS_INITIAUX;
        joueurs[i].couleur = i;

        if (charger_joueur(argv[i + 1], &joueurs[i]) != 0) {
            fprintf(stderr, "Erreur chargement joueur %d\n", i);
            return 1;
        }
    }

    lancer_partie(joueurs, nombre_joueurs);
    return 0;
}
