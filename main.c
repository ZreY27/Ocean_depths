#include <stdio.h>
#include <stdlib.h>
#include "code/include/affichage.h"
#include "code/include/joueur.h"
#include "code/include/creatures.h"
#include "code/include/carte.h"
#include "code/include/sauvegarde.h"


int main(void) {
    Plongeur joueur = initJoueur();
    CreatureMarine kraken = initCreature();
    //afficheCombat(&kraken, &joueur);
    Carte carte = initCarte(10, 5);
    afficherCarte(carte);
    sauvegarde(joueur, carte, "../code/saves/carteSaveTest.txt");
    for (int i = 0;i<10;i++) {
        afficheJoueurStat(&joueur);
        deplacement(&joueur, carte);
    }
    return 0;
}