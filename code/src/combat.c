#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "creatures.h"
#include "combat.h"
#include "inventaire.h"
#include "affichage.h"
#include "enum_etat.h"


// ----------------------- Développement des fonctions ----------------------- //

void lancerCombat(Plongeur* joueur, CreatureMarine* creature) {

    EtatFuite fuite_reussie_joueur = FUITE_ECHOUEEE;
    EtatFuite fuite_reussie_creature = FUITE_ECHOUEEE;
    reinitialiserPointsAction(joueur, creature);
    
    // Boucler le combat jusqu'à la mort du joueur ou de la créature ou qu'une fuite a été réussie (peu importe qui)
    while(joueur->points_de_vie_actuels > 0 && creature->points_de_vie_actuels > 0 && fuite_reussie_joueur == FUITE_ECHOUEEE && fuite_reussie_creature == FUITE_ECHOUEEE) {
        
        augmenterPointsAction(joueur, creature);
        //printf("Actions : Joueur=%d, Creature=%d\n", joueur->points_action, creature->points_action);

        switch (verifierSeuilAction(joueur, creature)) {

            case ACTION_JOUEUR:
                afficheCombat(creature, joueur);
                joueurAgit(joueur, creature, &fuite_reussie_joueur);
                break;
            
            case ACTION_CREATURE:
                afficheCombat(creature, joueur);
                creatureAgit(joueur, creature, &fuite_reussie_creature);
                break;

            case ACTION_DOUBLE:
                if(joueur->points_action >= creature->points_action) {
                    afficheCombat(creature, joueur);
                    joueurAgit(joueur, creature, &fuite_reussie_joueur);
                    if(creature->points_de_vie_actuels > 0) {
                        afficheCombat(creature, joueur);
                        creatureAgit(joueur, creature, &fuite_reussie_creature);
                    }
                } else {
                    afficheCombat(creature, joueur);
                    creatureAgit(joueur, creature, &fuite_reussie_creature);
                    if(joueur->points_de_vie_actuels > 0) {
                        afficheCombat(creature, joueur);
                        joueurAgit(joueur, creature, &fuite_reussie_joueur);
                    }
                }
                break;
            
            case AUCUNE_ACTION:
            default:
                break;
        }
    
    }

    //verifier fin de combat
    if (joueur->points_de_vie_actuels <= 0) {
        printf("Vous avez ete vaincu...\n");
    } else if (creature->points_de_vie_actuels <= 0) {
        printf("Vous avez vaincu la creature !\n");
    } else if (fuite_reussie_joueur == FUITE_REUSSIE) {
        printf("Vous avez reussi a fuir le combat !\n");
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
void enleverPointsActionTourJoueur(Plongeur* joueur){
    joueur->points_action -= SEUIL_ACTION;
}
void enleverPointsActionTourCreature(CreatureMarine* creature){
    creature->points_action -= SEUIL_ACTION;
}

// Version finale
EtatAction verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature) {
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

ValidationAttaque verifierFatigue(int niveau_fatigue, ImpactFatigue impact_fatigue) {
    if(niveau_fatigue+impact_fatigue > 3) {
        return ATTAQUE_INVALIDE;
    } else {
        return ATTAQUE_VALIDE;
    }
}

// Version finale
int calculerChanceFuite(int vitesseAllie, int vitesseEnnemi, int niveauFatigue) {
    int chanceFuite = 100;

   // --- Influence de la différence de vitesse ---
    int difference = (int)(((double)(vitesseEnnemi - vitesseAllie) / vitesseAllie) * 100.0);

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
void joueurAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_etat) {

    // Vérifie les effets de statut avant d'agir

    // Empoisonnement
    if(joueur->est_empoisonne == EST_EMPOISONNE) {
        joueur->points_de_vie_actuels -= joueur->points_de_vie_max * 0.05; // Perte de 5% des PV max
        printf("Le plongeur souffre du poison.\n");
        if (joueur->points_de_vie_actuels <= 0) {
            return; // Le joueur meurt, il ne peut pas agir
        }
    }

    // Étourdissement
    if (joueur->est_etourdi == EST_ETOURDI){
        joueur->est_etourdi = N_EST_PAS_ETOURDI; // L'effet d'étourdissement dure un tour
        printf("Le plongeur est etourdi et ne peut pas agir ce tour-ci.\n");
        return; // Le joueur perd son tour
    }
    
    // Enleve la garde supplémentaire (si prise de position défensive au tour précédent)
    joueur->defense_supplementaire = 0;

    int choix_qui_met_fin_tour = PAS_FIN_DE_TOUR;
    
    while(!choix_qui_met_fin_tour) {

        // Exemple d'actions
        printf("Choisissez une action :\n");
        printf("1. Action de combat\n");
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
                choix_qui_met_fin_tour = ouvrirInventaire(joueur, creature);
                break;
            
            case 3:
                ouvrirBestiaire();
                break;
            
            case 4:
                *fuite_etat = fuir(calculerChanceFuite(joueur->vitesse, creature->vitesse, joueur->niveau_fatigue));
                choix_qui_met_fin_tour = FIN_DE_TOUR; // Fuir met fin au tour
                break;

            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;

        }
    }

    enleverPointsActionTourJoueur(joueur);

}

FinDeTour choixAttaque(Plongeur* joueur, CreatureMarine* creature){
    
    int attaque_valide = ATTAQUE_INVALIDE;
    
    while (attaque_valide == ATTAQUE_INVALIDE){

        printf("Choisissez votre attaque :\n");
        printf("1. Attaque legere\n");
        printf("2. Attaque lourde\n");
        printf("3. Defense\n");
        printf("4. Repos\n");
        printf("0. Retour au choix du joueur\n");

       ChoixAttaquePlongeur attaque;
       
       scanf("%d", &attaque);

        switch (attaque) {

            case ATTAQUE_LEGERE:
                attaqueLegere(joueur, creature);
                attaque_valide = ATTAQUE_VALIDE;
                break;

            case ATTAQUE_LOURDE:
                attaqueLourde(joueur, creature);
                attaque_valide = ATTAQUE_VALIDE;
                break;
            
            case DEFENSE:
                defense(joueur);
                attaque_valide = ATTAQUE_VALIDE;
                break;

            case REPOS:
                repos(joueur);
                attaque_valide = ATTAQUE_VALIDE;
                break;
                
            case RETOUR_CHOIX_JOUEUR:
                return PAS_FIN_DE_TOUR;
            
            default:
                printf("Choix invalide.\n");
                break;
        }
    }

    // Sécurité : attaque toujours valide ici
    return FIN_DE_TOUR;
}

// ----------------------------------- CRÉATURE ---------------------------------- //

// Version améliorable
void creatureAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_reussie) {
    
    // -- Vérifie les effets de statut avant d'agir --

    // Empoisonnement
    if (creature->est_empoisonne > N_EST_PAS_EMPOISONNE) {
        creature->points_de_vie_actuels -= creature->points_de_vie_max * 0.05; // Perte de 5% des PV max
        creature->est_empoisonne--;
        printf("La creature souffre du poison.\n");
        if (creature->points_de_vie_actuels <= 0) {
            return; // La créature meurt, elle ne peut pas agir
        }
    }

    // Étourdissement
    if (creature->est_etourdi > N_EST_PAS_ETOURDI){
        creature->est_etourdi--;
        printf("La creature est etourdie et ne peut pas agir ce tour-ci.\n");
        return; // La créature perd son tour
    }

    // Enleve la garde supplémentaire (si prise de position défensive au tour précédent)
    creature->defense_supplementaire = 0;

    // -- La créature joue son tour --
    // Tableau de probabilités cumulées (en pourcentage)
    int probabilites[NB_CHOIX_CREATURE] = {10, 50, 80, 97, 100};
    // Correspond à : 10%, +40%, +30%, +17%, +3%

    int random_value = rand() % 100;
    ChoixAttaqueCreature action_aleatoire = NB_CHOIX_CREATURE; // Valeur par défaut

    for (int i = 0; i < NB_CHOIX_CREATURE; i++) {
        if (random_value < probabilites[i]) {
            action_aleatoire = i;
            break;
        }
    }

    switch (action_aleatoire)
    {
    case EXAMINE_ATTENTIVEMENT_CREATURE:
        creatureExamineAttentivement();
        break;
    
    case ATTAQUE_BASIQUE_CREATURE:
        creatureAttaque(joueur, creature);
        break;

    case ATTAQUE_SPECIALE_CREATURE:
        creatureAttaqueSpeciale(joueur, creature);
        break;
    
    case DEFENSE_CREATURE:
        creatureDefense(creature);
        break;

    case FUITE_CREATURE:
        *fuite_reussie = creatureFuit(calculerChanceFuite(creature->vitesse, joueur->vitesse, creature->niveau_fatigue));
        break;

    // Juste au cas où
    default:
        creatureExamineAttentivement();
        break;
    }

    enleverPointsActionTourCreature(creature);
}





