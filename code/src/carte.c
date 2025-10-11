#include <stdlib.h>
#include <stdio.h>
#include "../include/carte.h"
#include <time.h>


Case initCase(TypeCase type) {
    Case _case;
    _case.type = type;
    _case.visible = 1;
    _case.joueur = 0;
    return _case;
}


Carte initCarte(int hauteur, int longueur) {
    Carte carte;
    carte.longueur = longueur;
    carte.hauteur = hauteur;
    carte.cases = malloc(sizeof(Case*) * hauteur);

    srand(time(NULL)); // Initialisation du random

    for (int i = 0; i < hauteur; i++) {
        carte.cases[i] = malloc(sizeof(Case) * longueur);

        for (int j = 0; j < longueur; j++) {
            TypeCase type;

            if (i == 0) {
                type = SURFACE;
            } else {
                // Plus on descend, plus les types profonds deviennent possibles
                int maxType = i;
                if (maxType > PROFONDEUR) maxType = PROFONDEUR;

                type = (TypeCase)(rand() % (maxType + 1)); // valeur entre 0 et maxType

                if (type == SURFACE) type = ALGUES; // éviter surface sous l’eau
            }

            carte.cases[i][j] = initCase(type);

            if (i == 0 && j == 0) {
                carte.cases[i][j].joueur = 1;
            }
        }
    }
    return carte;
}

// Renvoie l'emoji correspondant au type de case
const char* getEmojiForType(TypeCase type) {
    switch (type) {
        case SURFACE: return "⛵";
        case VIDE: return "🌊";
        case ALGUES: return "🌿";
        case EPAVE: return "💰";
        case GROTTE: return "🕳️";
        case PROFONDEUR: return "🐙";
        default: return "❓";
    }
}