#ifndef INVENTAIRE_H
#define INVENTAIRE_H

typedef enum {
    SOIN,
    FLASH,
    TORPILLE_DE_POCHE,
    DIFFUSEUR_TOXIQUE,
} TypeObjet;


typedef enum {
    POING,
    COUTEAU,
    HARPON,
    LASER
} TypeArme;

typedef struct {
    int type;
    char* nom;
    char* description;

} Objet;

typedef struct {
    TypeArme arme;
    int capacite;
    int nb_objets;
    Objet* objets;
} Inventaire;

Inventaire initInventaire();

#endif