#ifndef CREATURE_H
#define CREATURE_H

#include "enum_etat.h"
typedef struct Plongeur Plongeur;

typedef struct CreatureMarine{
    int id;  // identifiant unique pour cibler
    char nom[30];

    int points_de_vie_max;
    int points_de_vie_actuels;
    
    int attaque_minimale;
    int attaque_maximale;
    
    int defense;
    int defense_supplementaire; // bonus temporaire en combat lors de la prise de position défensive

    int niveau_fatigue; // 0 à 3
    int vitesse;
    int effet_special; // "paralysie : 2", "poison : 1", "aucun : 0"
    int est_vivant;

    int points_action; // ATB en combat (Active Time Battle)
    int a_fui; // 0 = non, 1 = oui
    int est_empoisonne; // 0 = non, 1 = oui
    int est_etourdi; // 0 = non, 1 = oui

}CreatureMarine;

typedef enum{
    AUCUN_EFFET_SPECIAL,
    EFFET_POISON,
    EFFET_PARALYSIE,
    EFFET_POISON_PARALYSIE
} EffetSpecialCreature;

CreatureMarine initCreature();

// -- COMBAT --

char* creatureExamineAttentivement(CreatureMarine* creature, char* message); // Faite
int creatureAttaque(Plongeur* joueur, CreatureMarine* creature); // Faite
void creatureAttaqueSpeciale(Plongeur* joueur, CreatureMarine* creature, char* message, char* effet_special); // Faite
void creatureDefense(CreatureMarine* creature); // Faite
EtatFuite creatureFuit(int chanceFuite); // Faite

int esquiveCreature(CreatureMarine* creature); // Faite

#endif