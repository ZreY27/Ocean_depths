#include <stdio.h>
#include <stdlib.h>
#include "code/include/affichage.h"
#include "code/include/joueur.h"
#include "code/include/creatures.h"

int main(void) {
    Plongeur joueur = init_joueur();
    CreatureMarine kraken = init_creature();
    affiche_combat(&kraken, &joueur);
    return 0;
}