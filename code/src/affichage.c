#include<stdio.h>
#include<stdlib.h>
#include "../include/affichage.h"
#include "../include/creatures.h"
#include "../include/joueur.h"

void affiche_combat(CreatureMarine * creature, Plongeur * joueur) {
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