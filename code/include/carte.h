#ifndef CARTE_H
#define CARTE_H
#include "creatures.h"
#include "inventaire.h"

typedef enum {
    SURFACE = 0,
    ALGUES   = 1,
    EPAVE   = 2,
    GROTTE  = 3,
    PROFONDEUR = 4
} TypeCase;

typedef struct {
    TypeCase type;
    CreatureMarine creature;
    //Objet objets[10];
    //int nbObjets;
    int visible;
    int joueur;
}Case;

typedef struct {
    int hauteur;
    int longueur;
    Case **cases;
}Carte;

Case initCase(TypeCase type);
Carte initCarte(int hauteur, int longueur);

#endif
