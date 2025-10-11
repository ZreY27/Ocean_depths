#ifndef JOUEUR_H
#define JOUEUR_H

#include "carte.h"

typedef struct {
     int points_de_vie;
     int points_de_vie_max;
     int niveau_oxygene;
     int niveau_oxygene_max;
     int niveau_fatigue; // 0 à 5
     int perles; // monnaie du jeu
     int x;
     int y;
 }Plongeur;

Plongeur initJoueur();
void deplacement(Plongeur* joueur, Carte carte);

#endif
