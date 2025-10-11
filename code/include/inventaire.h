#ifndef INVENTAIRE_H
#define INVENTAIRE_H

typedef struct {
    int capacite;
    int nb_objets;
    Objet* objets;
} Inventaire;

typedef struct {
    int type;
} Objet;

#endif