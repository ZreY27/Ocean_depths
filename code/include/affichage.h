#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"

void afficheCombat(CreatureMarine * creature, Plongeur * joueur);
void afficherCarte(Carte carte);
void afficheJoueur(Plongeur * joueur);

#endif