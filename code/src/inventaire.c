#include "../include/inventaire.h"

#include <stdlib.h>

Inventaire initInventaire() {
    Inventaire inventaire;
    inventaire.capacite = 5;
    inventaire.nb_objets = 0;
    inventaire.objets = malloc(sizeof(Objet)*inventaire.capacite);
    inventaire.arme = POING;
    return inventaire;
}