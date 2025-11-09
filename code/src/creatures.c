#include<stdio.h>
#include<stdlib.h>
#include "../include/creatures.h"


CreatureMarine initCreature() {
    CreatureMarine creature;
    creature.id = 1;
    //creature.nom = malloc(sizeof(char*));
    creature.points_de_vie_max = 100;
    creature.points_de_vie_actuels = 100;

    creature.attaque_maximale = 7;
    creature.attaque_minimale = 1;

    creature.defense = 10;
    creature.defense_supplementaire = 0;

    creature.niveau_fatigue = 0;
    creature.vitesse = 5;
    creature.effet_special = AUCUN_EFFET_SPECIAL;
    creature.est_vivant = 1;
    
    creature.points_action = 0;
    creature.a_fui = 0;
    creature.est_empoisonne = 0;
    creature.est_etourdi = 0;

    return creature;
}



