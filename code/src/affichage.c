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
    printf("Joueur :\n");
    printf("[");
    for (int i = 0;i < joueur->points_de_vie_max;i++) {
        if (joueur->points_de_vie_actuels>=i) {
            printf("0");
        } else printf(".");
    }
    printf("]\n");

    printf("Mob : \n");
    printf("[");
    for (int i = 0;i < creature->points_de_vie_max;i++) {
        if (creature->points_de_vie_actuels>=i) {
            printf("0");
        } else printf(".");
    }
    printf("]\n\n");
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

void afficherJauge(const char* label, int valeur, int max) {
    int largeur = 20; // longueur de la barre
    int nbBloc = (valeur * largeur) / max;

    printf("%-10s [", label);
    for (int i = 0; i < largeur; i++) {
        if (i < nbBloc) printf("#");
        else printf("-");
    }
    printf("] %d/%d\n", valeur, max);
}

void afficheJoueurStat(Plongeur *joueur) {
    printf("\n===== STATS DU PLONGEUR =====\n");

    afficherJauge("❤️ Vie", joueur->points_de_vie_actuels, joueur->points_de_vie_max);
    afficherJauge("💧 Oxygène", joueur->niveau_oxygene, joueur->niveau_oxygene_max);

    printf("😴 Fatigue : %d / 5\n", joueur->niveau_fatigue);
    printf("💎 Perles  : %d\n", joueur->perles);

    printf("=============================\n\n");
}

void nettoyerAffichage() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}