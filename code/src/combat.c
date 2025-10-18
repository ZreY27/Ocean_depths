#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "creatures.h"
#include "combat.h"
#include "creatures.h"
#include "inventaire.h"

#define SEUIL_ACTION 100 

// ----------------------- Développement des fonctions ----------------------- //

void lancerCombat(Plongeur* joueur, CreatureMarine* creature) {

    int fuite_reussie = 0;

    reinitialiserPointsAction(joueur, creature);
    
    // Boucler le combat jusqu'à la mort du joueur ou de la créature ou qu'une fuite a été réussie (peu importe qui)
    while(joueur->points_de_vie_actuels > 0 && creature->points_de_vie_actuels > 0 && !fuite_reussie) {
        
        

        augmenterPointsAction(joueur, creature);
        
        switch (verifierSeuilAction(joueur, creature)) {

            case ACTION_JOUEUR:
                joueurAgit(joueur, creature, &fuite_reussie);
                break;
            
            case ACTION_CREATURE:
                creatureAgit(joueur, creature, &fuite_reussie);
                break;

            case ACTION_DOUBLE:
                if(joueur->points_action >= creature->points_action) {
                    joueurAgit(joueur, creature, &fuite_reussie);
                    if(creature->points_de_vie_actuels > 0) {
                        creatureAgit(joueur, creature, &fuite_reussie);
                    }
                } else {
                    creatureAgit(joueur, creature, &fuite_reussie);
                    if(joueur->points_de_vie_actuels > 0) {
                        joueurAgit(joueur, creature, &fuite_reussie);
                    }
                }
                break;
            
            case AUCUNE_ACTION:
            default:
                break;
        }
    
    }
    
}

// Version finale
void reinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature) {
    joueur->points_action = 0;
    creature->points_action = 0;
}

// Version finale
void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature) {
    joueur->points_action += joueur->vitesse;
    creature->points_action += creature->vitesse;
}

// Version finale
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

// Version finale
int calculerChanceFuite(int vitesseJoueur, int vitesseEnnemi, int niveauFatigue) {
    int chanceFuite = 100;

   // --- Influence de la différence de vitesse ---
    int difference = (int)(((double)(vitesseEnnemi - vitesseJoueur) / vitesseJoueur) * 100.0);

    if (difference > 0) {
        // Ennemi plus rapide → malus
        chanceFuite -= difference;
    } else if (difference < 0) {
        // Joueur plus rapide → bonus
        chanceFuite += (-difference) / 2; // bonus atténué pour éviter 100% auto
    }

    // --- Influence de la fatigue ---
    chanceFuite -= niveauFatigue * 10;
    // --- Bornage ---
    if (chanceFuite < 0)  chanceFuite = 0;
    if (chanceFuite > 100) chanceFuite = 100;

    return chanceFuite;
}

// ----------------------------------- JOUEUR ----------------------------------- //

// Version améliorable
void joueurAgit(Plongeur* joueur, CreatureMarine* creature, int* fuite_reussie) {

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
                fuite_reussie = fuir(joueur, creature);
                choix_qui_met_fin_tour = 1; // Fuir met fin au tour
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;


        }
    }

}

int choixAttaque(Plongeur* joueur, CreatureMarine* creature){
    return 1; // Met fin au tour
}

int ouvrirInventaire(Plongeur* joueur){
    return 0; // Ne met pas fin au tour
}

int utiliserObjet(Plongeur* joueur, CreatureMarine* creature){
    return 1; // Met fin au tour
}

int fuir(Plongeur* joueur, CreatureMarine* creature){

    int chanceFuite = calculerChanceFuite(joueur->vitesse, creature->vitesse, joueur->niveau_fatigue);
    int tirage = rand() % 100;
    printf("Chance de fuite : %d%%, Tirage : %d\n", chanceFuite, tirage);

    if (tirage < chanceFuite) {

        printf("Fuite réussie !\n");
        return FUITE_REUSSIE;

    } else {

        printf("Fuite échouée !\n");
        return FUITE_ECHOUEEE;

    }
}

void ouvrirBestiaire(){

}

// ----------------------------------- CRÉATURE ---------------------------------- //

// Version améliorable
void creatureAgit(Plongeur* joueur, CreatureMarine* creature, int* fuite_reussie) {
    
    // -- Vérifie les effets de statut avant d'agir --

    // Empoisonnement
    if (creature->est_empoisonne == 1) {
        creature->points_de_vie_actuels -= creature->points_de_vie_max * 0.05; // Perte de 5% des PV max
        if (creature->points_de_vie_actuels <= 0) {
            return; // La créature meurt, elle ne peut pas agir
        }
    }

    // Étourdissement
    if (creature->est_etourdi == 1){
        creature->est_etourdi = 0; // L'effet d'étourdissement dure un tour
        return; // La créature perd son tour
    }

    // -- La créature joue son tour --

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
        // creatureFuit(joueur, creature);
        break;  

    // Juste au cas où
    default:
        creatureJugeDeFou();
        break;
    }
}

void creatureJugeDeFou(){
    int texte_aleatoire = rand() % 3;
    switch (texte_aleatoire)
    {
    case 0:
        printf("La créature vous observe avec curiosité.");
        break;
    
    case 1:
        printf("La créature émet un son étrange.");
        break;

    case 2:
        printf("La créature nage en cercles autour de vous.");
        break;

    default:
        break;
    }
    
}

void creatureAttaque(Plongeur* joueur, CreatureMarine* creature){
    printf("La créature attaque !\n");
}

void creatureFuit(Plongeur* joueur, CreatureMarine* creature){
    printf("La créature a fui !\n");
}

