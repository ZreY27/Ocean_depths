#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "creatures.h"
#include "combat.h"
#include "inventaire.h"
#include "affichage.h"
#include "enum_etat.h"


// ----------------------- Développement des fonctions ----------------------- //

EtatFinCombat lancerCombat(Plongeur* joueur, CreatureMarine* creature) {

    EtatFuite fuite_reussie_joueur = FUITE_ECHOUEEE;
    EtatFuite fuite_reussie_creature = FUITE_ECHOUEEE;
    reinitialiserPointsAction(joueur, creature);
    
    // Boucler le combat jusqu'à la mort du joueur ou de la créature ou qu'une fuite a été réussie (peu importe qui)
    while(joueur->points_de_vie_actuels > 0 && creature->points_de_vie_actuels > 0 && fuite_reussie_joueur == FUITE_ECHOUEEE && fuite_reussie_creature == FUITE_ECHOUEEE) {
        
        //afficheCombat(creature, joueur); avec la valeur de points d'action mise à jour
        augmenterPointsAction(joueur, creature);
        //printf("Actions : Joueur=%d, Creature=%d\n", joueur->points_action, creature->points_action);

        switch (verifierSeuilAction(joueur, creature)) {

            case ACTION_JOUEUR:{
                
                joueurAgit(joueur, creature, &fuite_reussie_joueur);
                break;
            }
            
            case ACTION_CREATURE:
            
                creatureAgit(joueur, creature, &fuite_reussie_creature);
                break;

            case ACTION_DOUBLE:
                if(joueur->points_action >= creature->points_action) {
                    
                    joueurAgit(joueur, creature, &fuite_reussie_joueur);
                    if(creature->points_de_vie_actuels > 0) {
                    
                        creatureAgit(joueur, creature, &fuite_reussie_creature);
                    }
                } else {
                    
                    creatureAgit(joueur, creature, &fuite_reussie_creature);
                    if(joueur->points_de_vie_actuels > 0) {
                    
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
        return DEFAITE;
    } else if (creature->points_de_vie_actuels <= 0) {
        printf("Vous avez vaincu la creature !\n");
        int arme = rand() % 4;
        if (arme < 3) {
            ajoutArme(&joueur->inventaire, arme);
        }
        return VICTOIRE;
    } else if (fuite_reussie_joueur == FUITE_REUSSIE) {
        printf("Vous avez reussi a fuir le combat !\n");
        return FUITE;
    }
    else if(fuite_reussie_creature == FUITE_REUSSIE){
        printf("La creature vous a file entre les doigts, skill issue btw.");
        return FUITE;
    }
    else{
        printf("Par la magie du saint esprit (bug), le combat s'est terminé. Skill issue de la part des dev btw.");
        return FUITE;
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
void enleverPointsActionTourJoueur(Plongeur* joueur){
    joueur->points_action -= SEUIL_ACTION;
}

// Version finale
void enleverPointsActionTourCreature(CreatureMarine* creature){
    creature->points_action -= SEUIL_ACTION;
}

// Version finale
EtatAction verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature) {
    int joueurPret = joueur->points_action >= SEUIL_ACTION ? 1 : 0;
    int creaturePrete = creature->points_action >= SEUIL_ACTION ? 1 : 0;

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

// Version Finale
void joueurAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_etat) {
    
    char message[256];
    char menu[256];
    sprintf(message, "C'est a votre tour.");
    sprintf(menu, "Chargement...");
    afficherCombat(creature, joueur, message, menu);

    // Vérifie les effets de statut avant d'agir

    // Empoisonnement
    if(joueur->est_empoisonne > N_EST_PAS_EMPOISONNE) {
        joueur->points_de_vie_actuels -= joueur->points_de_vie_max * 0.05; // Perte de 5% des PV max
        sprintf(message, "Vous subissez les effets du poison.");
        afficherCombat(creature, joueur, message, menu);
        joueur->est_empoisonne--;
        if (joueur->points_de_vie_actuels <= 0) {
            return; // Le joueur meurt, il ne peut pas agir
        }
    }

    // Étourdissement
    if (joueur->est_etourdi == EST_ETOURDI){
        joueur->est_etourdi = N_EST_PAS_ETOURDI; // L'effet d'étourdissement dure un tour
        sprintf(message, "Vous etes étourdi et ne pouvez pas agir.");
        afficherCombat(creature, joueur, message, menu);
        return; // Le joueur perd son tour
    }
    
    // Enleve la garde supplémentaire (si prise de position défensive au tour précédent)
    joueur->defense_supplementaire = 0;

    int choix_qui_met_fin_tour = PAS_FIN_DE_TOUR;
    
    while(!choix_qui_met_fin_tour) {

        // Exemple d'actions
        sprintf(message, "Choisissez une action :");
        sprintf(menu, "1. Action de combat\n2. Utiliser un objet\n3. Ouvrir le bestiaire\n4. Fuir");
        afficherCombat(creature, joueur, message, menu);

        int choix;
        scanf(" %d", &choix);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choix) {
            
            case 1:
                choix_qui_met_fin_tour = choixAttaque(joueur, creature, message, menu);
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
                sprintf(message, "Choix invalide. Veuillez reessayer.");
                sprintf(menu, "1. Action de combat\n2. Utiliser un objet\n3. Ouvrir le bestiaire\n4. Fuir");
                afficherCombat(creature, joueur, message, menu);
                break;

        }
    }

    enleverPointsActionTourJoueur(joueur);

}

FinDeTour choixAttaque(Plongeur* joueur, CreatureMarine* creature, char* message, char* menu){
    
    int attaque_valide = ATTAQUE_INVALIDE;
    
    while (attaque_valide == ATTAQUE_INVALIDE){

        sprintf(message, "Choisissez une action de combat :");
        sprintf(menu, "1. Attaque legere\n2. Attaque lourde\n3. Defense\n4. Repos\n0. Retour");
        afficherCombat(creature, joueur, message, menu);

        ChoixAttaquePlongeur attaque;
       
        scanf(" %d", &attaque);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        sprintf(menu, "En attente...");
        int degats;
       
        switch (attaque) {

            case ATTAQUE_LEGERE:
                degats = attaqueLegere(joueur, creature);
                sprintf(message, "Vous infligez %d points de degats a la creature.", degats);
                afficherCombat(creature, joueur, message, menu);
                attaque_valide = ATTAQUE_VALIDE;
                break;

            case ATTAQUE_LOURDE:
                degats = attaqueLourde(joueur, creature);
                sprintf(message, "Vous infligez %d points de degats a la creature.", degats);
                afficherCombat(creature, joueur, message, menu);
                attaque_valide = ATTAQUE_VALIDE;
                break;
            
            case DEFENSE:
                defense(joueur);
                sprintf(message, "Vous prenez une position defensive.");
                afficherCombat(creature, joueur, message, menu);
                attaque_valide = ATTAQUE_VALIDE;
                break;

            case REPOS:
                repos(joueur);
                sprintf(message, "Vous prenez un moment pour vous reposer.");
                afficherCombat(creature, joueur, message, menu);
                attaque_valide = ATTAQUE_VALIDE;
                break;
                
            case RETOUR_CHOIX_JOUEUR:
                return PAS_FIN_DE_TOUR;
            
            default:
                sprintf(message, "Choix invalide.");
                afficherCombat(creature, joueur, message, menu);
                break;
        }
    }

    // Sécurité : attaque toujours valide ici
    return FIN_DE_TOUR;
}

// ----------------------------------- CRÉATURE ---------------------------------- //

// Version améliorable
void creatureAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_reussie) {
    
    char message[256];
    char menu[256];
    sprintf(message, "C'est au tour de la creature");
    sprintf(menu, "En attente...");
    afficherCombat(creature, joueur, message, menu);

    // -- Vérifie les effets de statut avant d'agir --

    // Empoisonnement
    if (creature->est_empoisonne > N_EST_PAS_EMPOISONNE) {
        creature->points_de_vie_actuels -= creature->points_de_vie_max * 0.05; // Perte de 5% des PV max
        creature->est_empoisonne--;
        sprintf(message, "La creature souffre du poison.");
        afficherCombat(creature, joueur, message, menu);
        if (creature->points_de_vie_actuels <= 0) {
            return; // La créature meurt, elle ne peut pas agir
        }
    }

    // Étourdissement
    if (creature->est_etourdi > N_EST_PAS_ETOURDI){
        creature->est_etourdi--;
        sprintf(message, "La creature est etourdie et ne peut pas agir ce tour-ci.");
        afficherCombat(creature, joueur, message, menu);
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
        creatureExamineAttentivement(message);
        afficherCombat(creature, joueur, message, menu);
        break;
    
    case ATTAQUE_BASIQUE_CREATURE:{
        int degats = creatureAttaque(joueur, creature);
        afficherCombat(creature, joueur, message, menu);
        break;
    }
    case ATTAQUE_SPECIALE_CREATURE:{
        char effet_special[256];
        creatureAttaqueSpeciale(joueur, creature, message, effet_special);
        afficherCombat(creature, joueur, message, menu);
        afficherCombat(creature, joueur, effet_special, menu);
        break;
    }
    case DEFENSE_CREATURE:
        sprintf(message,"La creature prend une position defensive.");
        afficherCombat(creature, joueur, message, menu);
        creatureDefense(creature);
        break;

    case FUITE_CREATURE:{
        int chanceFuite = calculerChanceFuite(creature->vitesse, joueur->vitesse, creature->niveau_fatigue);
        sprintf(message,"La creature tente de fuir le combat. (%d%% de chance)", chanceFuite);
        afficherCombat(creature, joueur, message, menu);
        *fuite_reussie = creatureFuit(chanceFuite);
        if (*fuite_reussie)
        {
            sprintf(message, "La creature a reussi a fuir le combat !");
            afficherCombat(creature, joueur, message, menu);
        }
        else
        {
            sprintf(message, "La creature a echoue a fuir le combat.");
            afficherCombat(creature, joueur, message, menu);
        }
        break;
    }   
    // Juste au cas où
    default:
        creatureExamineAttentivement(message);
        afficherCombat(creature, joueur, message, menu);
        break;
    }

    enleverPointsActionTourCreature(creature);
}





