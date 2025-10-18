#ifndef CREATURE_H
#define CREATURE_H

typedef struct {
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
    char effet_special[20]; // "paralysie", "poison", "aucun"
    int est_vivant;

    int points_action; // ATB en combat (Active Time Battle)
    int a_fui; // 0 = non, 1 = oui
    int est_empoisonne; // 0 = non, 1 = oui
    int est_etourdi; // 0 = non, 1 = oui

}CreatureMarine;

/*
typedef enum {
    OBSERVE,
    ATTAQUE_LEGERE,
    ATTAQUE_LOURDE,
    //CRIE_DE_GUERRE,
    //CRIE_INTIMIDANT,
    FUITE,
    NB_ACTION_POSSIBLE
} PlageActionCreature;
 */

CreatureMarine initCreature();

#endif