#ifndef JOUEUR_H
#define JOUEUR_H
#include "inventaire.h"

#include "carte.h"

typedef struct {
     int points_de_vie_actuels;
     int points_de_vie_max;
     int niveau_oxygene;
     int niveau_oxygene_max;
     int niveau_fatigue; // 0 à 5
     int perles; // monnaie du jeu

     int vitesse; // influence l'ordre d'action en combat
     int points_action; // ATB en combat (Active Time Battle)
     int attaque_minimale;
     int attaque_maximale;
     int defense;

     Inventaire inventaire;
  
     int x;
     int y;
 }Plongeur;

Plongeur initJoueur();
void deplacement(Plongeur* joueur, Carte carte);

#endif
