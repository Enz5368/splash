# Projet Splashmem IA

Splashmem est un jeu de conquête de grille en C. Quatre programmes (joueurs) s'affrontent sur un plateau de 100x100 cases. L'objectif est de marquer le plus de cases possible avant d'épuiser son crédit d'actions.

## 📋 Spécifications du jeu

Grille : 100 x 100 cases (Coordonnées 0,0 en haut à gauche).

Crédits : Chaque joueur dispose de 9000 points.

Moteur graphique : Développé avec SDL2.

## 🕹️ Actions et Coûts

ACTION_MOVE_X   
Coûts : 1   
Déplace d'une case et la marque.

ACTION_DASH_X  
Coûts : 10  
Déplace de 8 cases et marque tout le trajet.

ACTION_TELEPORT_X   
Coûts : 2   
Téléporte de 8 cases, seule la case d'arrivée est marquée.

ACTION_STILL    
Coûts : 1   
Aucune action.

## 🛠️ Installation et Compilation

``` git clone https://github.com/Enz5368/splash.git ``` 

``` cd splash ```

Prérequis

Le projet nécessite les bibliothèques SDL2 et SDL2_ttf installées sur votre système Linux.

```sudo apt-get install libsdl2-dev libsdl2-ttf-dev```


## Compilation

Pour compiler le moteur de jeu (splash) et l'ensemble des joueurs présents dans le dossier players/ :

```make```


## 🚀 Lancement

Le programme splash nécessite le chemin vers les 4 fichiers .so des joueurs :

```./splash players/random_player.so players/random_player1.so players/random_player2.so players/random_player3.so```


## 🧠 Création d'une IA (Joueur)

Chaque joueur est une bibliothèque dynamique qui doit exporter au minimum la fonction suivante :

```char get_action();```


Elle doit renvoyer un code action défini dans actions.h. Pour compiler manuellement un nouveau joueur :

```gcc -Wall -Wextra -fPIC -shared -Iinclude -o players/mon_ia.so players/mon_ia.c```


## 📁 Structure du projet

src/ : Code source du moteur de jeu et du rendu.

include/ : Fichiers d'en-tête et polices (TTF).

players/ : Codes sources des joueurs IA.

Makefile : Script de build automatisé.
