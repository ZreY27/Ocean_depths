#include <stdlib.h>
#include <stdio.h>
#include "../include/carte.h"


Case initCase(TypeCase type) {
    Case _case;
    _case.type = type;
    _case.visible = 0;
    _case.joueur = 0;
    return _case;
}

Carte initCarte(int hauteur, int longueur) {
    Carte carte;
    carte.longueur = longueur;
    carte.hauteur = hauteur;
    carte.cases = malloc(sizeof(Case*) * hauteur);
    for (int i = 0; i < hauteur; i++) {
        carte.cases[i] = malloc(sizeof(Case) * longueur);
        for (int j = 0; j < longueur; j++) {
            carte.cases[i][j] = initCase(SURFACE);
            if (i == 0 && j == 0) {
                carte.cases[i][j].joueur = 1;
            }
        }
    }
    return carte;
}