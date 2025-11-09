#ifndef JOUEUR_H
#define JOUEUR_H

#include "inventaire.h"
#include "carte.h"
typedef struct CreatureMarine CreatureMarine;

typedef enum {
    FATIGUE_AUCUNE,
    FATIGUE_LEGERE,
    FATIGUE_MODEREE,
    FATIGUE_ELEVEE
} NiveauFatigue;



typedef struct Plongeur{
    int points_de_vie_actuels;
    int points_de_vie_max;
    int niveau_oxygene;
    int niveau_oxygene_max;
    int niveau_fatigue; // 0 à 3
    int perles; // monnaie du jeu
 
    int vitesse; // influence l'ordre d'action en combat
    int points_action; // ATB en combat (Active Time Battle)
    int attaque_minimale;
    int attaque_maximale;
    int defense;
    int defense_supplementaire; // bonus temporaire en combat lors de la prise de position défensive

    int a_fui; // 0 = non, 1 = oui
    int est_empoisonne; // 0 = non, 1 = oui
    int est_etourdi; // 0 = non, 1 = oui

    Inventaire inventaire;
  
    int x;
    int y;
 
}Plongeur;

Plongeur initJoueur();
void deplacement(Plongeur* joueur, Carte carte);

// -- Combat --
void attaqueLegere(Plongeur* joueur, CreatureMarine* creature); // Faite
void attaqueLourde(Plongeur* joueur, CreatureMarine* creature); // Faite
void defense(Plongeur* joueur); // Faite
void repos(Plongeur* joueur); // Faite

FinDeTour ouvrirInventaire(Plongeur* joueur, CreatureMarine* creature); //TODO
int utiliserObjet(Plongeur* joueur, CreatureMarine* creature); //TODO
EtatFuite fuir(int chanceFuite); // Faite
void ouvrirBestiaire(); // <<< BONUS POSSIBLE

int esquiveJoueur(Plongeur* joueur); // <<< BONUS POSSIBLE

#endif
