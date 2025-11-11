#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"

void afficherCombat(const CreatureMarine * creature, const Plongeur * joueur, const char* message, const char* menu);
void afficherBarrePV(int pv_actuels, int pv_max, int longueur);
void afficherCarte(Carte carte);

void afficheJoueurStat(Plongeur * joueur);

void afficheJoueur(Plongeur * joueur);
void nettoyerAffichage();


#endif