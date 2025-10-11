#ifndef CARTE_H
#define CARTE_H
#include "creatures.h"
#include "inventaire.h"

typedef enum {
    SURFACE,
    VIDE,
    ALGUES,
    EPAVE,
    GROTTE,
    PROFONDEUR
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
} Carte;

Case initCase(TypeCase type);
Carte initCarte(int hauteur, int longueur);
const char* getEmojiForType(TypeCase type);

#endif
