#include<stdio.h>
#include<stdlib.h>
#include "../include/sauvegarde.h"
#include "../include/joueur.h"
#include "../include/carte.h"


void sauvegarde(Plongeur joueur, Carte carte, char * path) {
    FILE * fichier = NULL;
    if ((fichier = fopen(path,"w")) == NULL) {
        printf("Erreur\n");
    }
    fprintf(fichier, "CARTE;%d;%d\n", carte.hauteur, carte.longueur);
    fprintf(fichier, "JOUEUR;%d;%d;%d;%d;%d\n", joueur.points_de_vie_actuels, joueur.points_de_vie_max, joueur.niveau_oxygene, joueur.niveau_oxygene_max, joueur.niveau_fatigue, joueur.perles);
    for(int i=0;i<carte.hauteur;i++) {
        for(int j=0;j<carte.longueur;j++) {
            fprintf(fichier, "CASE;%d;%d;%d;%d;%d;%d\n", i, j, carte.cases[i][j].type, carte.cases[i][j].creature.id, carte.cases[i][j].visible, carte.cases[i][j].joueur);
        }
    }
    fclose(fichier);
}