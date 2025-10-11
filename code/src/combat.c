#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "combat.h"
#include "creatures.h"
#include "inventaire.h"

#define SEUIL_ACTION 100 
/*
Seuil de points d'action pour pouvoir agir.
Chaque tour, chaque personnage gagne des points d'action en fonction de sa vitesse.
Une fois le seuil atteint, il peut agir (attaquer, utiliser un objet, etc.) 
et perd des points d'action.
*/
void lancerCombat(Plongeur* joueur, CreatureMarine* creature);

void réinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature);
void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature);
int verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature);

void joueurAgit(Plongeur* joueur, CreatureMarine* creature);
void creatureAgit(Plongeur* joueur, CreatureMarine* creature);

void choixAttaque(Plongeur* joueur, CreatureMarine* creature);
void utiliserObjet(Plongeur* joueur, CreatureMarine* creature);
void ouvrirBestiaire();
void fuir(Plongeur* joueur, CreatureMarine* creature);





void lancerCombat(Plongeur* joueur, CreatureMarine* creature) {

    reinitialiserPointsAction(joueur, creature);
    
    while(joueur->points_de_vie_actuels > 0 && creature->points_de_vie_actuels > 0) {
        
        augmenterPointsAction(joueur, creature);
        
        switch (verifierSeuilAction(joueur, creature)) {

            case ACTION_JOUEUR:
                joueurAgit(joueur, creature);
                break;
            
            case ACTION_CREATURE:
                creatureAgit(joueur, creature);
                break;

            case ACTION_DOUBLE:
                if(joueur->points_action >= creature->points_action) {
                    joueurAgit(joueur, creature);
                    if(creature->points_de_vie_actuels > 0) {
                        creatureAgit(joueur, creature);
                    }
                } else {
                    creatureAgit(joueur, creature);
                    if(joueur->points_de_vie_actuels > 0) {
                        joueurAgit(joueur, creature);
                    }
                }
                break;
            
            case AUCUNE_ACTION:
            default:
                break;
        }
    
    }
    
}


