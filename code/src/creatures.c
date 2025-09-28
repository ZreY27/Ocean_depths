#include<stdio.h>
#include<stdlib.h>
#include "../include/creatures.h"


CreatureMarine initCreature() {
    CreatureMarine creature;
    creature.id = 1;
    //creature.nom = malloc(sizeof(char*));
    creature.points_de_vie_max = 100;
    creature.points_de_vie_actuels = 100;
    creature.attaque_maximale = 100;
    creature.attaque_minimale = 100;
    creature.defense = 100;
    creature.vitesse = 100;
    //creature.effet_special = malloc(sizeof(char*));
    creature.est_vivant = 1;
    return creature;
}
