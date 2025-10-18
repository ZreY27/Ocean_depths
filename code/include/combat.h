#ifndef COMBAT_H
#define COMBAT_H

typedef enum {
    AUCUNE_ACTION,
    ACTION_JOUEUR,
    ACTION_CREATURE,
    ACTION_DOUBLE
} EtatAction;

typedef enum{
    FUITE_ECHOUEEE,
    FUITE_REUSSIE
} EtatFuite;

typedef enum {
    RETOUR_CHOIX_JOUEUR,
    ATTAQUE_LEGERE,
    ATTAQUE_LOURDE,
    DEFENSE,
    REPOS
} choixAttaquePlongeur;

typedef enum {
    A_ATTAQUE,
    A_PAS_ATTAQUE
} EtatAttaquePlongeur;

typedef enum {
    ATTAQUE_INVALIDE,
    ATTAQUE_VALIDE
} ValidationAttaquePlongeur;

typedef enum{
    PAS_FIN_DE_TOUR,
    FIN_DE_TOUR
} FinDeTourPlongeur;

/*
Seuil de points d'action pour pouvoir agir.
Chaque tour, chaque personnage gagne des points d'action en fonction de sa vitesse.
Une fois le seuil atteint, il peut agir (attaquer, utiliser un objet, etc.) 
et perd des points d'action.
*/
void lancerCombat(Plongeur* joueur, CreatureMarine* creature); // En cours...

void reinitialiserPointsAction(Plongeur* joueur, CreatureMarine* creature); // Faite
void augmenterPointsAction(Plongeur* joueur, CreatureMarine* creature); // Faite
EtatAction verifierSeuilAction(Plongeur* joueur, CreatureMarine* creature); // Faite
int calculerChanceFuite(int vitesseJoueur, int vitesseEnnemi, int niveauFatigue); // Faite

void joueurAgit(Plongeur* joueur, CreatureMarine* creature, int* fuite_reussie); // Version améliorable

/* 
Fonctions à déplacer dans joueur.c ou inventaire.c + creature.c plus tard
Les actions qui mettent fin au tour du joueur retournent 1, les autres 0.
Cette implémentation permet de laisser le joueur revenir sur sa décision d'attaque ou non.
À terme, il y aura plusieurs choix d'attaques (comme des compétences spéciales, etc.)
*/
FinDeTourPlongeur choixAttaque(Plongeur* joueur, CreatureMarine* creature); // En cours...
void attaqueLegere(Plongeur* joueur, CreatureMarine* creature); //TODO
void attaqueLourde(Plongeur* joueur, CreatureMarine* creature); //TODO
void defense(Plongeur* joueur); // Faite
void repos(Plongeur* joueur); // Faite

FinDeTourPlongeur ouvrirInventaire(Plongeur* joueur); //TODO
int utiliserObjet(Plongeur* joueur, CreatureMarine* creature); //TODO
EtatFuite fuir(Plongeur* joueur, CreatureMarine* creature); // Faite
void ouvrirBestiaire(); // <<< BONUS POSSIBLE

int esquiveJoueur(Plongeur* joueur); // TODO

/*
Algorithme et système d'IA à peaufiner plus tard. 
Pour l'instant effectue une action aléatoire simple.
*/
void creatureAgit(Plongeur* joueur, CreatureMarine* creature, int* fuite_reussie); // Version améliorable

void creatureJugeDeFou(); // Faite
void creatureAttaque(Plongeur* joueur, CreatureMarine* creature); //TODO
void creatureFuit(Plongeur* joueur, CreatureMarine* creature); //TODO

int esquiveCreature(CreatureMarine* creature); // TODO

#endif