#include<stdio.h>
#include<stdlib.h>
#include "../include/joueur.h"

Plongeur init_joueur() {
    Plongeur joueur;
    joueur.points_de_vie = 100;
    joueur.points_de_vie_max = 100;
    joueur.niveau_oxygene = 100;
    joueur.niveau_oxygene_max = 100;
    joueur.niveau_fatigue = 0;
    joueur.perles = 0;
    return  joueur;
}