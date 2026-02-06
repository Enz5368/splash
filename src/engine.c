#include "engine.h"
#include "actions.h"
#include "grid.h"
#include <stdio.h>

static int deplacement_x(Action action)
{
    if (action == ACTION_DEPLACER_DROITE || action == ACTION_DASH_DROITE || action == ACTION_TELEPORT_DROITE)
        return 1;
    if (action == ACTION_DEPLACER_GAUCHE || action == ACTION_DASH_GAUCHE || action == ACTION_TELEPORT_GAUCHE)
        return -1;
    return 0;
}

static int deplacement_y(Action action)
{
    if (action == ACTION_DEPLACER_BAS || action == ACTION_DASH_BAS || action == ACTION_TELEPORT_BAS)
        return 1;
    if (action == ACTION_DEPLACER_HAUT || action == ACTION_DASH_HAUT || action == ACTION_TELEPORT_HAUT)
        return -1;
    return 0;
}

static int multiplicateur(Action action)
{
    if (action >= ACTION_DASH_GAUCHE && action <= ACTION_DASH_BAS)
        return 8;
    if (action >= ACTION_TELEPORT_GAUCHE && action <= ACTION_TELEPORT_BAS)
        return 8;
    return 1;
}

void lancer_partie(Joueur joueurs[], int nombre_joueurs)
{
    Grille grille;
    initialiser_grille(&grille);

    int joueurs_actifs = nombre_joueurs;

    while (joueurs_actifs > 0) {
        joueurs_actifs = 0;

        for (int i = 0; i < nombre_joueurs; i++) {
            Joueur *j = &joueurs[i];

            if (j->credits <= 0)
                continue;

            joueurs_actifs++;

            Action action = j->get_action();
            int cout = cout_action(action);

            if (j->credits < cout)
                continue;

            j->credits -= cout;

            int dx = deplacement_x(action);
            int dy = deplacement_y(action);
            int mult = multiplicateur(action);

            j->x = (j->x + dx * mult + LARGEUR_GRILLE) % LARGEUR_GRILLE;
            j->y = (j->y + dy * mult + HAUTEUR_GRILLE) % HAUTEUR_GRILLE;

            marquer_case(&grille, j->x, j->y, j->id);
        }
    }

    printf("Partie terminée.\n");
    afficher_scores(&grille, nombre_joueurs);
}
