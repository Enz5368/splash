#include "engine.h"
#include "actions.h"
#include "grid.h"
#include "render.h"

#include <stdio.h>
#include <SDL2/SDL.h>

/* Déplacement en x selon l'action (conforme aux noms du sujet)  */
static int deplacement_x(char action)
{
    if (action == ACTION_MOVE_R || 
        action == ACTION_DASH_R || 
        action == ACTION_TELEPORT_R)
        return 1;

    if (action == ACTION_MOVE_L || 
        action == ACTION_DASH_L || 
        action == ACTION_TELEPORT_L)
        return -1;

    return 0;
}

/* Déplacement en y selon l'action (conforme aux noms du sujet)  */
static int deplacement_y(char action)
{
    if (action == ACTION_MOVE_D || 
        action == ACTION_DASH_D || 
        action == ACTION_TELEPORT_D)
        return 1;

    if (action == ACTION_MOVE_U || 
        action == ACTION_DASH_U || 
        action == ACTION_TELEPORT_U)
        return -1;

    return 0;
}

/* Distance de déplacement selon le type d'action  */
static int distance_action(char action)
{
    // DASH et TELEPORT déplacent de 8 cases 
    if (action == ACTION_DASH_L || action == ACTION_DASH_R || 
        action == ACTION_DASH_U || action == ACTION_DASH_D ||
        action == ACTION_TELEPORT_L || action == ACTION_TELEPORT_R || 
        action == ACTION_TELEPORT_U || action == ACTION_TELEPORT_D) {
        return 8;
    }
    return 1;
}

void lancer_partie(Joueur joueurs[], int nombre_joueurs)
{
    Grille grille;
    initialiser_grille(&grille);
    initialiser_rendu();

    int actifs = 1;

    // Le jeu s'arrête quand tous les joueurs n'ont plus de crédit 
    while (actifs > 0) {
        actifs = 0;

        for (int i = 0; i < nombre_joueurs; i++) {
            Joueur *j = &joueurs[i];

            if (j->credits <= 0) continue;

            actifs++;

            // Appel de la fonction du joueur (doit retourner un char) 
            char action = j->get_action();
            int cout = cout_action(action);

            if (j->credits >= cout) {
                j->credits -= cout;

                int dx = deplacement_x(action);
                int dy = deplacement_y(action);
                int dist = distance_action(action);

                for (int d = 0; d < dist; d++) {
                    // Effet Pacman : retour au côté opposé 
                    j->x = (j->x + dx + LARGEUR_GRILLE) % LARGEUR_GRILLE;
                    j->y = (j->y + dy + HAUTEUR_GRILLE) % HAUTEUR_GRILLE;

                    // On ne marque les cases intermédiaires que pour MOVE et DASH.
                    if (action != ACTION_TELEPORT_L && action != ACTION_TELEPORT_R &&
                        action != ACTION_TELEPORT_U && action != ACTION_TELEPORT_D) {
                        marquer_case(&grille, j->x, j->y, j->id);
                    }
                }
                
                // Marquage de la destination finale 
                marquer_case(&grille, j->x, j->y, j->id);
            }
        }

        afficher_grille(&grille);
        SDL_Delay(10); 
    }

    printf("Fin de la partie ! \n");
    afficher_scores(&grille, nombre_joueurs);
    fermer_rendu();
}