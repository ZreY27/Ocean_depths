#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"

void afficheCombat(CreatureMarine * creature, Plongeur * joueur);
void afficherCarte(Carte carte);
void afficheJoueur(Plongeur * joueur);
void nettoyerAffichage();

void nettoyerAffichage() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif