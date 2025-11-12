#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"

typedef enum{
    AFFICHAGE_LENT,
    AFFICHAGE_NORMAL,
    AFFICHAGE_RAPIDE
} EtatAffichage;

void afficherCombat(const CreatureMarine * creature, const Plongeur * joueur, 
    const char* message, const char* menu, EtatAffichage etat_affichage); // Faite
void afficherBarrePV(int pv_actuels, int pv_max, int longueur); // Faite
void afficheInventaire(Inventaire inventaire);
void afficherCarte(Carte carte);

void afficheJoueurStat(Plongeur * joueur);

void afficheJoueur(Plongeur * joueur);
void nettoyerAffichage();


#endif