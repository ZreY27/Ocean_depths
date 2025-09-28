#include <stdlib.h>
#include <stdio.h>
#include "../include/carte.h"


Case initCase(TypeCase type) {
    Case _case;
    _case.type = type;
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
        }
    }
    return carte;
}