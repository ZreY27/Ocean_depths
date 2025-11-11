#include "../include/inventaire.h"

#include <stdlib.h>
#include <stdio.h>

Inventaire initInventaire() {
    Inventaire inventaire;
    inventaire.capacite = 5;
    inventaire.nb_objets = 0;
    inventaire.objets = malloc(sizeof(Objet)*inventaire.capacite);
    inventaire.arme = POING;
    return inventaire;
}

void ajoutIventaire(Inventaire* inventaire, int objet) {
    Objet new_objet;
    new_objet.type = objet;
    printf("vous avez trouvé un objet !\n");
    if (inventaire->nb_objets == inventaire->capacite) {
        int index;
        printf("L'inventaire est déjà plein !\n");
        printf("Entrez le numéro de l'objet à poser ou 0 pour ne rien faire :\n");
        scanf("%d", &index);
        if (index > inventaire->capacite) {
            printf("Saisie incorrecte\n");
        }
        else if (index != 0) {
            inventaire->objets[index-1] = new_objet;
        }
    }
    else {
        inventaire->objets[inventaire->nb_objets] = new_objet;
        inventaire->nb_objets++;
    }
}