#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/joueur.h"
#include "../include/carte.h"
#include "../include/affichage.h"

#include "carte.h"



Plongeur initJoueur() {
    Plongeur joueur;
    joueur.points_de_vie_actuels = 100;
    joueur.points_de_vie_max = 100;
    joueur.niveau_oxygene = 100;
    joueur.niveau_oxygene_max = 100;
    joueur.vitesse = 10;
    joueur.niveau_fatigue = 0;
    joueur.perles = 0;
    joueur.x = 0;
    joueur.y = 0;
    return  joueur;
}

void deplacement(Plongeur* joueur, Carte carte) {
    char saisie;

    printf("Utilisez zqsd pour vous déplacer : ");
    scanf(" %c", &saisie);  // espace avant %c pour ignorer '\n'

    int newX = joueur->x;
    int newY = joueur->y;

    // Détermination de la direction
    switch (saisie) {
        case 'z': // haut
            newY--;
            break;
        case 's': // bas
            newY++;
            break;
        case 'q': // gauche
            newX--;
            break;
        case 'd': // droite
            newX++;
            break;
        default:
            printf("Erreur de saisie !\n");
            deplacement(joueur, carte); // redemande une saisie
            return;
    }

    // Vérifie les limites de la carte
    if (newX < 0 || newX >= carte.longueur || newY < 0 || newY >= carte.hauteur) {
        printf("Impossible de se déplacer ici (hors de la carte) !\n");
        deplacement(joueur, carte); // redemande
        return;
    }


    // Met à jour la position du joueur
    carte.cases[joueur->y][joueur->x].joueur = 0;  // ancienne position
    joueur->x = newX;
    joueur->y = newY;
    joueur->niveau_fatigue++;
    if (newX == 0) {
        joueur->niveau_oxygene += 100;
        joueur->niveau_oxygene % joueur->niveau_oxygene_max;
    } else joueur->niveau_oxygene_max -= newX;
    carte.cases[joueur->y][joueur->x].joueur = 1;  // nouvelle position
    carte.cases[joueur->y][joueur->x].visible = 1;  // nouvelle position

    afficherCarte(carte);
}
