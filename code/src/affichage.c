#include<stdio.h>
#include<stdlib.h>
#include "../include/affichage.h"
#include "../include/creatures.h"
#include "../include/joueur.h"
#include "../include/carte.h"

void afficheCombat(CreatureMarine * creature, Plongeur * joueur) {
    printf("OceanDepths - Profondeur:       ");
    printf("Perles : %d\n", joueur->perles);

    //affiche la vie du joueur
    printf("[");
    for (int i = 0;i < joueur->points_de_vie_max;i++) {
        if (joueur->points_de_vie>=i) {
            printf("0");
        } else printf(".");
    }
    printf("]");
}

void afficherCarte(Carte carte) {
    for (int i = 0; i < carte.hauteur; i++) {
        for (int j = 0; j < carte.longueur; j++) {

            if (carte.cases[i][j].joueur == 1) {
                printf("🤿 "); // position du joueur
            }
            else if (carte.cases[i][j].visible == 0) {
                printf("⬛ "); // zone non explorée
            }
            else {
                printf("%s ", getEmojiForType(carte.cases[i][j].type));
            }
        }
        printf("\n");
    }

    printf("\n");
}

void afficheJoueur(Plongeur * joueur) {
    printf("");
}