#include "../include/inventaire.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        if (index > inventaire->capacite || index < 0) {
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

void consomerObjet(Inventaire* inventaire, int index) {
    for (int i = index-1; i < inventaire->nb_objets-1; i++) {
        inventaire->objets[i] = inventaire->objets[i + 1];
    }
    inventaire->objets[inventaire->nb_objets - 1] = (Objet){0};
    inventaire->nb_objets -= 1;
}

void ajoutArme(Inventaire* inventaire, int arme) {
    if (arme>=inventaire->arme) {
        inventaire->arme = arme;
        printf("Vous avez gagné une nouvelle arme !");
        switch (inventaire->arme) {
            case POING :
                printf("✊");
                break;
            case COUTEAU :
                printf("🔪");
                break;
            case HARPON :
                printf("🎯");
                break;
            case LASER :
                printf("🔫");
                break;
            default :
                printf("⬛ ");
                break;
        }
        printf("\n");
    }
}

void stringInventaire(Inventaire* inventaire, char* message) {
    sprintf(message, " ");

    char ligne[64]; // tampon pour chaque ajout

    // 🔹 Parcours de chaque slot
    for (int i = 0; i < inventaire->capacite; i++) {
        if (i < inventaire->nb_objets) {
            char emoji[8] = "⬛";

            switch (inventaire->objets[i].type) {
                case SOIN: strcpy(emoji, "💊"); break;
                case FLASH: strcpy(emoji, "⚡"); break;
                case TORPILLE_DE_POCHE: strcpy(emoji, "💣"); break;
                case DIFFUSEUR_TOXIQUE: strcpy(emoji, "☠️"); break;
                default: strcpy(emoji, "⬛"); break;
            }

            snprintf(ligne, sizeof(ligne), "%d.%s  ", i + 1, emoji);
        } else {
            snprintf(ligne, sizeof(ligne), "%d.⬛  ", i + 1);
        }

        strcat(message, ligne);
    }
    // 🔹 Ajout de l’option de retour
    strcat(message, " 0. Retour\n");
    // 🔹 Ajout de l’arme actuelle
    strcat(message, "Arme : ");
    switch (inventaire->arme) {
        case POING: strcat(message, "✊"); break;
        case COUTEAU: strcat(message, "🔪"); break;
        case HARPON: strcat(message, "🎯"); break;
        case LASER: strcat(message, "🔫"); break;
        default: strcat(message, "⬛"); break;
    }
}