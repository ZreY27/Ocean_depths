#include <stdio.h>
#include <stdlib.h>
#include "code/include/affichage.h"
#include "code/include/joueur.h"
#include "code/include/creatures.h"
#include "code/include/carte.h"

int main(void) {
    Plongeur joueur = initJoueur();
    CreatureMarine kraken = initCreature();
    //affiche_combat(&kraken, &joueur);
    Carte carte = initCarte(3, 3);
    afficherCarte(carte);
    return 0;
}