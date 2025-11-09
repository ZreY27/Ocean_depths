#include<stdio.h>
#include<stdlib.h>
#include "../include/creatures.h"
#define MULTIPLICATEUR_ATTAQUE_SPECIALE_CREATURE 1.5

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

// -------------------------------------- COMBAT ------------------------------------ 

void creatureExamineAttentivement(){
    int texte_aleatoire = (int) (rand() % 3);
    switch (texte_aleatoire)
    {
    case 0:
        printf("La creature vous observe avec curiosite.\n");
        break;
    
    case 1:
        printf("La creature emet un son etrange.\n");
        break;

    case 2:
        printf("La creature nage en cercles autour de vous.\n");
        break;

    default:
        printf("CA BUUUUUUUUUUUUUUUUUUUUUUUUUUUUG\n");
        break;
    }
    
}

void creatureAttaque(Plongeur* joueur, CreatureMarine* creature){


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

    // affiche les dégâts infligés
    printf("La creature vous inflige %d points de degats.\n", degat);
}

void creatureAttaqueSpeciale(Plongeur* joueur, CreatureMarine* creature){
    
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
    printf("La creature vous inflige %d points de degats avec son attaque speciale.\n", degat);

    // applique l'effet spécial si la créature en a un avec une probabilité de propre à la créature
    switch (creature->effet_special) {
        case EFFET_POISON:
            if ((rand() % 100) < 30) { // 30% de chance d'empoisonner
                joueur->est_empoisonne = EST_EMPOISONNE;
                printf("La creature vous a empoisonne !\n");
            }
            break;
        
        case EFFET_PARALYSIE:
            if ((rand() % 100) < 20) { // 20% de chance d'étourdir
                joueur->est_etourdi = EST_ETOURDI;
                printf("La creature vous a etourdi !\n");
            }
            break;

        case AUCUN_EFFET_SPECIAL:
        default:
            break;
    }
    
}

void creatureDefense(CreatureMarine* creature){
    //augmente de 50% la défense de la créature jusqu'au prochain tour
    creature->defense_supplementaire = creature->defense / 2;

}

EtatFuite creatureFuit(Plongeur* joueur, CreatureMarine* creature){
    int chanceFuite = calculerChanceFuite(creature->vitesse, joueur->vitesse, creature->niveau_fatigue);
    int tirage = rand() % 100;
    printf("Chance de fuite : %d%%, Tirage : %d\n", chanceFuite, tirage);

    if (tirage < chanceFuite) {

        printf("La créature s'est enfuie !\n");
        return FUITE_REUSSIE;

    } else {

        printf("La creature a tente de s'enfuir mais elle est tombee comme du n'importe quoi, on dirait la giraffe qui s'emmele les pattes quoi !\n");
        return FUITE_ECHOUEEE;

    }
}



