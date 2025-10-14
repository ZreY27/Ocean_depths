#ifndef INVENTAIRE_H
#define INVENTAIRE_H

typedef enum {
    SOIN,
    FLASH,
    TORPILLE_DE_POCHE,
    DIFFUSEUR_TOXIQUE,

} TypeObjet;

typedef struct {
    int type;
    char* nom;
    char* description;

} Objet;

typedef struct {
    int capacite;
    int nb_objets;
    Objet* objets;
} Inventaire;

#endif