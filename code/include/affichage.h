#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"
void afficheInventaire(Inventaire inventaire);
void afficheCombat(CreatureMarine * creature, Plongeur * joueur);
void afficherCarte(Carte carte);

void afficheJoueurStat(Plongeur * joueur);

void afficheJoueur(Plongeur * joueur);
void nettoyerAffichage();


#endif