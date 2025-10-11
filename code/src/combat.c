#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "creatures.h"
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

void reinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature);
void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature);
int verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature);

void joueurAgit(Plongeur* joueur, CreatureMarine* creature);

/*
Algorithme et système d'IA à peaufiner plus tard. 
Pour l'instant effectue une action aléatoire simple.
*/
void creatureAgit(Plongeur* joueur, CreatureMarine* creature); // <<< BONUS POSSIBLE

/* 
Fonctions à déplacer dans joueur.c ou inventaire.c + creature.c plus tard
Les actions qui mettent fin au tour du joueur retournent 1, les autres 0.
Cette implémentation permet de laisser le joueur revenir sur sa décision d'attaque ou non.
À terme, il y aura plusieurs choix d'attaques (comme des compétences spéciales, etc.)
*/
int choixAttaque(Plongeur* joueur, CreatureMarine* creature); //TODO
int ouvrirInventaire(Plongeur* joueur); //TODO
int utiliserObjet(Plongeur* joueur, CreatureMarine* creature); //TODO
int fuir(Plongeur* joueur, CreatureMarine* creature); //TODO
void ouvrirBestiaire(); // <<< BONUS POSSIBLE


void creatureJugeDeFou(); //TODO
void creatureAttaque(Plongeur* joueur, CreatureMarine* creature); //TODO
void creatureFuit(Plongeur* joueur, CreatureMarine* creature); //TODO


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

void reinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature) {
    joueur->points_action = 0;
    creature->points_action = 0;
}

void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature) {
    joueur->points_action += joueur->vitesse;
    creature->points_action += creature->vitesse;
}

int verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature) {
    int joueurPret = (joueur->points_action >= SEUIL_ACTION);
    int creaturePrete = (creature->points_action >= SEUIL_ACTION);

    if(joueurPret && !creaturePrete) {
        return ACTION_JOUEUR;
    } 
    else if(!joueurPret && creaturePrete) {
        return ACTION_CREATURE;
    } 
    else if(joueurPret && creaturePrete) {
        return ACTION_DOUBLE;
    } 
    else {
        return AUCUNE_ACTION;
    }
}

void joueurAgit(Plongeur* joueur, CreatureMarine* creature) {

    int choix_qui_met_fin_tour = 0;
    
    while(!choix_qui_met_fin_tour) {

        // Exemple d'actions
        printf("Choisissez une action :\n");
        printf("1. Attaquer\n");
        printf("2. Utiliser un objet\n");
        printf("3. Ouvrir le bestiaire\n");
        printf("4. Fuir\n");


        int choix;
        scanf("%d", &choix);


        switch (choix) {
            case 1:
                choix_qui_met_fin_tour = choixAttaque(joueur, creature);
                break;

            case 2:
                choix_qui_met_fin_tour = utiliserObjet(joueur, creature);
                break;
            
            case 3:
                ouvrirBestiaire();
                break;
            
            case 4:
                choix_qui_met_fin_tour = fuir(joueur, creature);
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;


        }
    }


}

void creatureAgit(Plongeur* joueur, CreatureMarine* creature) {
    int action_aleatoire = rand() % 3;

    switch (action_aleatoire)
    {
    case 0:
        creatureJugeDeFou();
        break;

    case 1:
        creatureAttaque(joueur, creature);
        break;
        
    case 2:
        creatureFuit(joueur, creature);
        break;  

    // Juste au cas où
    default:
        creatureJugeDeFou();
        break;
    }
    
}