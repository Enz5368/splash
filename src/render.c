#include "render.h"
#include <stdio.h>

void initialiser_affichage(void)
{
    printf("Affichage initialisé\n");
}

void afficher_etat(const Grille *grille, Joueur joueurs[], int nombre_joueurs)
{
    (void)grille;
    (void)joueurs;
    (void)nombre_joueurs;
}

void fermer_affichage(void)
{
    printf("Affichage fermé\n");
}
