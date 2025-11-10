#ifndef COMBAT_H
#define COMBAT_H

#define SEUIL_ACTION 100 

typedef enum {
    AUCUNE_ACTION,
    ACTION_JOUEUR,
    ACTION_CREATURE,
    ACTION_DOUBLE
} EtatAction;

typedef enum {
    RETOUR_CHOIX_JOUEUR,
    ATTAQUE_LEGERE,
    ATTAQUE_LOURDE,
    DEFENSE,
    REPOS
} ChoixAttaquePlongeur;

typedef enum {
    EXAMINE_ATTENTIVEMENT_CREATURE,
    ATTAQUE_BASIQUE_CREATURE,
    ATTAQUE_SPECIALE_CREATURE,
    DEFENSE_CREATURE,
    FUITE_CREATURE,
    NB_CHOIX_CREATURE
} ChoixAttaqueCreature;

typedef enum {
    A_ATTAQUE,
    A_PAS_ATTAQUE
} EtatAttaquePlongeur;

typedef enum {
    ATTAQUE_INVALIDE,
    ATTAQUE_VALIDE
} ValidationAttaque;

typedef enum{
    IMPACT_FATIGUE_AUCUN,
    IMPACT_FATIGUE_FAIBLE,
    IMPACT_FATIGUE_ELEVEE
} ImpactFatigue;

typedef enum{
    VICTOIRE,
    DEFAITE,
    FUITE
} EtatFinCombat;

/*
Seuil de points d'action pour pouvoir agir.
Chaque tour, chaque personnage gagne des points d'action en fonction de sa vitesse.
Une fois le seuil atteint, il peut agir (attaquer, utiliser un objet, etc.) 
et perd des points d'action.
*/
EtatFinCombat lancerCombat(Plongeur* joueur, CreatureMarine* creature); // En cours...

void reinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature); // Faite
void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature); // Faite
void enleverPointsActionTourJoueur(Plongeur* joueur); // Faite
void enleverPointsActionTourCreature(CreatureMarine* creature); // Faite

EtatAction verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature); // Faite
ValidationAttaque verifierFatigue(int niveau_fatigue, ImpactFatigue impact_fatigue); // Faite

int calculerChanceFuite(int vitesseJoueur, int vitesseEnnemi, int niveauFatigue); // Faite

/* 
Les actions qui mettent fin au tour du joueur retournent 1, les autres 0.
Cette implémentation permet de laisser le joueur revenir sur sa décision d'attaque ou non.
*/
void joueurAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_reussie); // Version améliorable

FinDeTour choixAttaque(Plongeur* joueur, CreatureMarine* creature); // En cours...

/*
Actions pour la créature.
*/
void creatureAgit(Plongeur* joueur, CreatureMarine* creature, EtatFuite* fuite_reussie); // Faite

#endif