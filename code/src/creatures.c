#include<stdio.h>
#include<stdlib.h>
#include "../include/creatures.h"
#include "../include/joueur.h"
#define MULTIPLICATEUR_ATTAQUE_SPECIALE_CREATURE 1.5

CreatureMarine initCreature() {
    CreatureMarine creature;
    creature.id = 1;
    //creature.nom = malloc(sizeof(char*));
    creature.points_de_vie_max = 100;
    creature.points_de_vie_actuels = 100;

    creature.attaque_maximale = 7*4;
    creature.attaque_minimale = 1*7;

    creature.defense = 10;
    creature.defense_supplementaire = 0;

    creature.niveau_fatigue = 0;
    creature.vitesse = 5;
    creature.effet_special = EFFET_POISON_PARALYSIE;
    creature.est_vivant = 1;
    
    creature.points_action = 0;
    creature.a_fui = 0;
    creature.est_empoisonne = 0;
    creature.est_etourdi = 0;

    return creature;
}

// -------------------------------------- COMBAT ------------------------------------ 

char* creatureExamineAttentivement(CreatureMarine* creature ,char* message){

    if(creature->niveau_fatigue > 1){
        creature->niveau_fatigue -= 2;
    } else {
        creature->niveau_fatigue = 0;
    }

    int texte_aleatoire = (int) (rand() % 3);
    switch (texte_aleatoire)
    {
    case 0:
        sprintf(message,"La creature vous observe avec curiosite.\n");
        return message;
    
    case 1:
        sprintf(message,"La creature emet un son etrange.\n");
        return message;

    case 2:
        sprintf(message,"La creature nage en cercles autour de vous.\n");
        return message;

    default:
        sprintf(message,"CA BUUUUUUUUUUUUUUUUUUUUUUUUUUUUG\n");
        return message;
    }
    
}

int creatureAttaque(Plongeur* joueur, CreatureMarine* creature){


    // calcul des dégâts brutes en fonction des statistiques d'attaque de la créature
    int degat = (rand() % (creature->attaque_maximale - creature->attaque_minimale + 1)) 
                + creature->attaque_minimale;
    
    // prise en compte de la défense du plongeur
    degat -= (joueur->defense + joueur->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%
    
    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }   

    // applique les dégâts au plongeur
    joueur->points_de_vie_actuels -= degat;

    // affecte la fatique de la créature
    creature->niveau_fatigue += 1;

    return degat;

    
}

void creatureAttaqueSpeciale(Plongeur* joueur, CreatureMarine* creature, char* message, char* effet_special){
    
    // calcul des dégâts brutes en fonction des statistiques d'attaque de la créature multipliées par 1.5
    int degat = (int)((rand() % (creature->attaque_maximale - creature->attaque_minimale + 1)) 
                + creature->attaque_minimale);

    // prise en compte de la défense du plongeur
    degat -= (joueur->defense + joueur->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%

    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }

    // Multiplicateur des dégâts
    degat = (int) (degat * MULTIPLICATEUR_ATTAQUE_SPECIALE_CREATURE);

    // applique les dégâts au plongeur
    joueur->points_de_vie_actuels -= degat;

    // affiche les dégâts infligés
    sprintf(message,"La creature vous inflige %d points de degats\n avec son attaque speciale.", degat);

    // applique l'effet spécial si la créature en a un avec une probabilité de propre à la créature
    switch (creature->effet_special) {
        case EFFET_POISON:
            if ((rand() % 100) < 30) { // 30% de chance d'empoisonner
                joueur->est_empoisonne = EST_EMPOISONNE;
                sprintf(effet_special,"La creature vous a empoisonne.");
            }
            break;
        
        case EFFET_PARALYSIE:
            if ((rand() % 100) < 20) { // 20% de chance d'étourdir
                joueur->est_etourdi = EST_ETOURDI;
                sprintf(effet_special,"La creature vous a paralyse.");
            }
            break;

        case EFFET_POISON_PARALYSIE:{
            int est_empoisonne = 0;
            int est_etourdi = 0;
            if ((rand() % 100) < 30) { // 30% de chance d'empoisonner
                joueur->est_empoisonne = EST_EMPOISONNE;
                est_empoisonne = 1;
                sprintf(effet_special,"La creature vous a empoisonne.");
            }
            if ((rand() % 100) < 20) { // 20% de chance d'étourdir
                joueur->est_etourdi = EST_ETOURDI;
                est_etourdi = 1;
                sprintf(effet_special,"La creature vous a paralyse.");
            }
            if (est_empoisonne && est_etourdi) {
                sprintf(effet_special,"La creature vous a empoisonne et paralyse.");
            }
            break;
        }
        case AUCUN_EFFET_SPECIAL:
        default:
            sprintf(effet_special,"", degat);
            break;
    }

    // affecte la fatique de la créature
    creature->niveau_fatigue += 2;
    
}

void creatureDefense(CreatureMarine* creature){
    //augmente de 50% la défense de la créature jusqu'au prochain tour
    creature->defense_supplementaire = creature->defense / 2;
    if(creature->niveau_fatigue > 0){
        creature->niveau_fatigue -= 1;
    }
}

EtatFuite creatureFuit(int chanceFuite){

    int tirage = rand() % 100;
    if (tirage < chanceFuite) {
        return FUITE_REUSSIE;
    } else {
        return FUITE_ECHOUEEE;
    }
}



