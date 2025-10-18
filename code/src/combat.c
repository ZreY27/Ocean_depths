#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "creatures.h"
#include "combat.h"
#include "creatures.h"
#include "inventaire.h"
#include "affichage.h"



// ----------------------- Développement des fonctions ----------------------- //

void lancerCombat(Plongeur* joueur, CreatureMarine* creature) {

    int fuite_reussie_joueur = FUITE_ECHOUEEE;
    int fuite_reussie_creature = FUITE_ECHOUEEE;
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
void joueurAgit(Plongeur* joueur, CreatureMarine* creature, int* fuite_etat) {

    // Vérifie les effets de statut avant d'agir

    // Empoisonnement
    if(joueur->est_empoisonne == EST_EMPOISONNE) {
        joueur->points_de_vie_actuels -= joueur->points_de_vie_max * 0.05; // Perte de 5% des PV max
        if (joueur->points_de_vie_actuels <= 0) {
            return; // Le joueur meurt, il ne peut pas agir
        }
    }

    // Étourdissement
    if (joueur->est_etourdi == EST_ETOURDI){
        joueur->est_etourdi = N_EST_PAS_ETOURDI; // L'effet d'étourdissement dure un tour
        return; // Le joueur perd son tour
    }
    
    // Enleve la garde supplémentaire (si prise de position défensive au tour précédent)
    joueur->defense_supplementaire = 0;

    int choix_qui_met_fin_tour = PAS_FIN_DE_TOUR;
    
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
                choix_qui_met_fin_tour = ouvrirInventaire(joueur, creature);
                break;
            
            case 3:
                ouvrirBestiaire();
                break;
            
            case 4:
                *fuite_etat = fuir(joueur, creature);
                choix_qui_met_fin_tour = FIN_DE_TOUR; // Fuir met fin au tour
                break;

            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;


        }
    }

    enleverPointsActionTourJoueur(joueur);

}

FinDeTourPlongeur choixAttaque(Plongeur* joueur, CreatureMarine* creature){
    
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

void attaqueLegere(Plongeur* joueur, CreatureMarine* creature){

    // calcul des dégâts brutes en fonction des statistiques d'attaque du plongeur
    int degat = (rand() % (joueur->attaque_maximale - joueur->attaque_minimale + 1)) 
                + joueur->attaque_minimale;

    // prise en compte de la défense de la créature
    degat -= (creature->defense + creature->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%

    // prise en compte des armes équipées
    degat += 5 * joueur->inventaire.arme; // Chaque niveau d'arme ajoute 5 dégâts

    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }
   
    // applique les dégâts à la créature
    creature->points_de_vie_actuels -= degat;
    
    // affiche les dégâts infligés
    printf("Vous infligez %d points de degats a la creature.\n", degat);

}

void attaqueLourde(Plongeur* joueur, CreatureMarine* creature){

    // calcul des dégâts brutes en fonction des statistiques d'attaque du plongeur multipliées par 3.5
        int degat = (int)((rand() % (joueur->attaque_maximale - joueur->attaque_minimale + 1)) 
                    + joueur->attaque_minimale);

    // prise en compte de la défense de la créature
    degat -= (creature->defense + creature->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%

    // prise en compte des armes équipées
    degat += 5 * joueur->inventaire.arme; // Chaque niveau d'arme ajoute 5 dégâts

    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }

    // multiplie les dégâts par le multiplicateur
    degat = (int)(degat * MULTIPLICATEUR_ATTAQUE_LOURDE);
   
    // applique les dégâts à la créature
    creature->points_de_vie_actuels -= degat;
    
    // affiche les dégâts infligés
    printf("Vous infligez %d points de degats a la creature.\n", degat);
}

void defense(Plongeur* joueur){
    //augmente de 50% la défense du plongeur jusqu'au prochain tour
    //redonne un peu d'energie : un point de fatigue (baisse la fatigue)
    joueur->defense_supplementaire = joueur->defense / 2;
    if(joueur->niveau_fatigue > 0){
        joueur->niveau_fatigue -= 1;
    }
}

void repos(Plongeur* joueur){
    //redonne deux points de fatigue (baisse la fatigue)
    if(joueur->niveau_fatigue > 1){
        joueur->niveau_fatigue -= 2;
    } else {
        joueur->niveau_fatigue = 0;
    }
}

FinDeTourPlongeur ouvrirInventaire(Plongeur* joueur, CreatureMarine* creature){
    return PAS_FIN_DE_TOUR;
}

int utiliserObjet(Plongeur* joueur, CreatureMarine* creature){
    return FIN_DE_TOUR;
}

EtatFuite fuir(Plongeur* joueur, CreatureMarine* creature){

    int chanceFuite = calculerChanceFuite(joueur->vitesse, creature->vitesse, joueur->niveau_fatigue);
    int tirage = rand() % 100;
    printf("Chance de fuite : %d%%, Tirage : %d\n", chanceFuite, tirage);

    if (tirage < chanceFuite) {

        printf("Fuite reussie !\n");
        return FUITE_REUSSIE;

    } else {

        printf("Fuite echouee !\n");
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
    if (creature->est_empoisonne == EST_EMPOISONNE) {
        creature->points_de_vie_actuels -= creature->points_de_vie_max * 0.05; // Perte de 5% des PV max
        if (creature->points_de_vie_actuels <= 0) {
            return; // La créature meurt, elle ne peut pas agir
        }
    }

    // Étourdissement
    if (creature->est_etourdi == EST_ETOURDI){
        creature->est_etourdi = N_EST_PAS_ETOURDI; // L'effet d'étourdissement dure un tour
        return; // La créature perd son tour
    }

    // Enleve la garde supplémentaire (si prise de position défensive au tour précédent)
    creature->defense_supplementaire = 0;

    // -- La créature joue son tour --
    ChoixAttaqueCreature action_aleatoire = (int) (rand() % NB_CHOIX_CREATURE);

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
        creatureFuit(joueur, creature);
        *fuite_reussie = FUITE_REUSSIE;
        break;

    // Juste au cas où
    default:
        creatureExamineAttentivement();
        break;
    }

    enleverPointsActionTourCreature(creature);
}

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
    printf("La creature attaque !\n");
}

void creatureAttaqueSpeciale(Plongeur* joueur, CreatureMarine* creature){
    printf("La creature utilise une attaque speciale !\n");
}

void creatureDefense(CreatureMarine* creature){
    printf("La creature se met en position defensive !\n");
}

void creatureFuit(Plongeur* joueur, CreatureMarine* creature){
    printf("La creature a fui !\n");
}

