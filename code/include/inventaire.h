#ifndef CARTE_H
#define CARTE_H

typedef struct {
    int capacite;
    int nb_objets;
    Objet* objets;
} Inventaire;

typedef struct {
    int type;
} Objet;

#endif