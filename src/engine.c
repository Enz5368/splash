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

static int trouver_ennemi_proche(Joueur joueurs[], int nb_joueurs, int id_joueur_actif) {
    int cible = -1;
    double dist_min = 10000.0;
    Joueur *actuel = &joueurs[id_joueur_actif];

    for (int i = 0; i < nb_joueurs; i++) {
        if (i == id_joueur_actif) continue;
        
        // Distance euclidienne (simplifiée pour une grille 100x100)
        double d = (joueurs[i].x - actuel->x)*(joueurs[i].x - actuel->x) + 
                   (joueurs[i].y - actuel->y)*(joueurs[i].y - actuel->y);
        if (d < dist_min) {
            dist_min = d;
            cible = i;
        }
    }
    return cible;
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

            // CRUCIAL : On ignore les joueurs morts, on incrémente les vivants
            if (j->credits <= 0) continue;
            actifs++;

            // 1. Gestion des Timers d'effets
            if (j->timer_mute > 0) j->timer_mute--;
            if (j->timer_swap > 0) j->timer_swap--;
            if (j->fork_active_timer > 0) {
                j->fork_active_timer--;
                if (j->fork_active_timer == 0) j->multiplicateur_cout = 1; 
            }

            // 2. Gestion de l'explosion des bombes
            if (j->bombe_posee) {
                j->bombe_timer--;
                if (j->bombe_timer == 0) {
                    // Explosion 3x3
                    for(int bx = -1; bx <= 1; bx++) {
                        for(int by = -1; by <= 1; by++) {
                            marquer_case(&grille, (j->bombe_x + bx + LARGEUR_GRILLE)%LARGEUR_GRILLE, 
                                                  (j->bombe_y + by + HAUTEUR_GRILLE)%HAUTEUR_GRILLE, j->id);
                        }
                    }
                    j->bombe_posee = false;
                }
            }
            
            // 3. Exécution de l'action
            char action = ACTION_STILL; // Sécurité par défaut

            if (j->is_txt) {
                if (j->nb_actions_txt > 0) {
                    // Lit le tableau en boucle 
                    action = j->actions_txt[j->index_action_txt];
                    j->index_action_txt = (j->index_action_txt + 1) % j->nb_actions_txt;
                }
            } else if (j->get_action != NULL) {
                // Appel standard pour les .so
                action = j->get_action();
            }
            
            
            int cout = cout_action(action, j->multiplicateur_cout);

            // Sécurité anti-freeze : Si le joueur n'a pas les moyens, il passe son tour
            if (j->credits < cout) {
                action = ACTION_STILL;
                cout = cout_action(action, j->multiplicateur_cout);
            }

            // On déduit l'argent et on joue
            j->credits -= cout;
            
            int dx = deplacement_x(action);
            int dy = deplacement_y(action);
            int dist = distance_action(action);

            // --- GESTION DES COULEURS (MUTE / SWAP) ---
            int id_a_marquer = j->id;
            if (j->timer_mute > 0) {
                id_a_marquer = -1; // Noir
            } else if (j->timer_swap > 0) {
                id_a_marquer = j->id_beneficiaire_swap; // Ennemi
            }

            // --- DÉPLACEMENT DU JOUEUR ORIGINAL ---
            for (int d = 0; d < dist; d++) {
                j->x = (j->x + dx + LARGEUR_GRILLE) % LARGEUR_GRILLE;
                j->y = (j->y + dy + HAUTEUR_GRILLE) % HAUTEUR_GRILLE;

                if (action != ACTION_TELEPORT_L && action != ACTION_TELEPORT_R &&
                    action != ACTION_TELEPORT_U && action != ACTION_TELEPORT_D) {
                    marquer_case(&grille, j->x, j->y, id_a_marquer);
                }
            }
            marquer_case(&grille, j->x, j->y, id_a_marquer);

            // --- DÉPLACEMENT DU CLONE (FORK) ---
            if (j->fork_en_attente) {
                j->fork_delay_timer--;
                if (j->fork_delay_timer <= 0) {
                    j->fork_en_attente = false;
                }
            } else if (j->fork_active_timer > 0) {
                for (int d = 0; d < dist; d++) {
                    j->fork_x = (j->fork_x + dx + LARGEUR_GRILLE) % LARGEUR_GRILLE;
                    j->fork_y = (j->fork_y + dy + HAUTEUR_GRILLE) % HAUTEUR_GRILLE;

                    if (action != ACTION_TELEPORT_L && action != ACTION_TELEPORT_R &&
                        action != ACTION_TELEPORT_U && action != ACTION_TELEPORT_D) {
                        marquer_case(&grille, j->fork_x, j->fork_y, id_a_marquer);
                    }
                }
                marquer_case(&grille, j->fork_x, j->fork_y, id_a_marquer);
            }
            
            // --- SWITCH DES CAPACITÉS SPÉCIALES ---
            switch(action) {
                case ACTION_BOMB:
                    if (!j->bombe_posee) {
                        j->bombe_posee = true;
                        j->bombe_timer = 5; 
                        j->bombe_x = j->x;
                        j->bombe_y = j->y;
                    }
                    break;

                case ACTION_CLEAN:
                    for(int cx = -3; cx <= 3; cx++) {
                        for(int cy = -3; cy <= 3; cy++) {
                            marquer_case(&grille, (j->x + cx + LARGEUR_GRILLE)%LARGEUR_GRILLE, 
                                                (j->y + cy + HAUTEUR_GRILLE)%HAUTEUR_GRILLE, -1);
                        }
                    }
                    break;

                case ACTION_MUTE: {
                    int cible_m = trouver_ennemi_proche(joueurs, nombre_joueurs, i);
                    if (cible_m != -1) {
                        joueurs[cible_m].timer_mute += 10; 
                        joueurs[cible_m].timer_swap = 0; 
                    }
                } break;

                case ACTION_SWAP: {
                    int cible_s = trouver_ennemi_proche(joueurs, nombre_joueurs, i);
                    if (cible_s != -1) {
                        joueurs[cible_s].timer_swap += 5; 
                        joueurs[cible_s].timer_mute = 0; 
                        joueurs[cible_s].id_beneficiaire_swap = j->id;
                    }
                } break;

                case ACTION_FORK:
                    if (j->fork_active_timer <= 0 && !j->fork_en_attente) {
                        j->fork_en_attente = true;
                        j->fork_delay_timer = 5;
                        j->fork_active_timer = 20;
                        j->fork_x = j->x; 
                        j->fork_y = j->y;
                        j->multiplicateur_cout = 2;
                    }
                    break;
            }
        }

        afficher_grille(&grille);
        SDL_Delay(10); 
    }

    printf("Fin de la partie ! \n");
    afficher_scores(&grille, nombre_joueurs);
    fermer_rendu();
}