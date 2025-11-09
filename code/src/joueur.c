#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/joueur.h"
#include "../include/carte.h"
#include "../include/affichage.h"
#include "../include/inventaire.h"
#include "../include/creatures.h"
#include "../include/enum_etat.h"

#define MULTIPLICATEUR_ATTAQUE_LOURDE 3.5

Plongeur initJoueur() {
    Plongeur joueur;

    joueur.points_de_vie_actuels = 100;
    joueur.points_de_vie_max = 100;
    joueur.niveau_oxygene = 100;
    joueur.niveau_oxygene_max = 100;
    joueur.vitesse = 10;
    joueur.niveau_fatigue = 0;
    joueur.perles = 0;

    joueur.attaque_minimale = 2;
    joueur.attaque_maximale = 5;

    joueur.defense = 5;
    joueur.defense_supplementaire = 0;

    joueur.a_fui = 0;
    joueur.est_empoisonne = 0;
    joueur.est_etourdi = 0;

    joueur.x = 0;
    joueur.y = 0;
    joueur.inventaire = initInventaire();
    return  joueur;
}

void deplacement(Plongeur* joueur, Carte carte) {
    char saisie;

    printf("Utilisez zqsd pour vous déplacer : ");
    scanf(" %s", &saisie);  // espace avant %c pour ignorer '\n'

    int newX = joueur->x;
    int newY = joueur->y;

    // Détermination de la direction
    switch (saisie) {
        case 'z': // haut
            newY--;
            break;
        case 's': // bas
            newY++;
            break;
        case 'q': // gauche
            newX--;
            break;
        case 'd': // droite
            newX++;
            break;
        default:
            printf("Erreur de saisie !\n");
            deplacement(joueur, carte); // redemande une saisie
            return;
    }

    // Vérifie les limites de la carte
    if (newX < 0 || newX >= carte.longueur || newY < 0 || newY >= carte.hauteur) {
        printf("Impossible de se déplacer ici (hors de la carte) !\n");
        deplacement(joueur, carte); // redemande
        return;
    }
    switch (carte.cases[newY][newX].type) {
        case ALGUES: {
            // 1 chance sur 5 de trouver 10 perles
            int chance = rand() % 5; // 0 à 4
            if (chance == 0) {
                joueur->perles += 10;
                printf("🌿 Vous fouillez les algues et trouvez 10 perles ! 💎\n");
            } else {
                printf("🌿 Rien d'intéressant dans ces algues...\n");
            }
            break;
        }
        case EPAVE: {
            // Soit 10 soit 50 perles (1 chance sur 2)
            int gain = (rand() % 2 == 0) ? 10 : 50;
            joueur->perles += gain;
            printf("⚓ Vous explorez une épave et trouvez %d perles ! 💰\n", gain);
            break;
        }
        default:
            break;
    }
    // Met à jour la position du joueur
    carte.cases[joueur->y][joueur->x].joueur = 0;  // ancienne position
    joueur->x = newX;
    joueur->y = newY;
    joueur->niveau_fatigue++;
    if (newY == 0) {
        joueur->niveau_oxygene += 99;
        joueur->niveau_oxygene = joueur->niveau_oxygene % joueur->niveau_oxygene_max;
    } else joueur->niveau_oxygene -= newY;
    carte.cases[joueur->y][joueur->x].joueur = 1;  // nouvelle position
    carte.cases[joueur->y][joueur->x].visible = 1;  // nouvelle position

    afficherCarte(carte);
}

// ---------------------------------- COMBAT -------------------------------------------------------

void attaqueLegere(Plongeur* joueur, CreatureMarine* creature){

    // calcul des dégâts brutes en fonction des statistiques d'attaque du plongeur
    int degat = (rand() % (joueur->attaque_maximale - joueur->attaque_minimale + 1)) 
                + joueur->attaque_minimale;

    // prise en compte de la défense de la créature
    degat -= (creature->defense + creature->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%

    // prise en compte des armes équipées
    degat += 5 * joueur->inventaire.arme; // Chaque niveau d'arme ajoute 5 dégâts

    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }
   
    // applique les dégâts à la créature
    creature->points_de_vie_actuels -= degat;
    
    // affiche les dégâts infligés
    printf("Vous infligez %d points de degats a la creature.\n", degat);

    // affecte la fatique du plongeur
    if(joueur->niveau_fatigue < 3){
        joueur->niveau_fatigue += 1;
    }

}

void attaqueLourde(Plongeur* joueur, CreatureMarine* creature){

    // calcul des dégâts brutes en fonction des statistiques d'attaque du plongeur multipliées par 3.5
    int degat = (int)((rand() % (joueur->attaque_maximale - joueur->attaque_minimale + 1)) 
             + joueur->attaque_minimale);

    // prise en compte de la défense de la créature
    degat -= (creature->defense + creature->defense_supplementaire) / 10; // La défense réduit les dégâts de 10%

    // prise en compte des armes équipées
    degat += 5 * joueur->inventaire.arme; // Chaque niveau d'arme ajoute 5 dégâts

    // s'assure que les dégâts ne sont pas négatifs
    if (degat < 0) {
        degat = 0;
    }

    // multiplie les dégâts par le multiplicateur
    degat = (int)(degat * MULTIPLICATEUR_ATTAQUE_LOURDE);
   
    // applique les dégâts à la créature
    creature->points_de_vie_actuels -= degat;
    
    // affiche les dégâts infligés
    printf("Vous infligez %d points de degats a la creature.\n", degat);
}

void defense(Plongeur* joueur){
    //augmente de 50% la défense du plongeur jusqu'au prochain tour
    //redonne un peu d'energie : un point de fatigue (baisse la fatigue)
    joueur->defense_supplementaire = joueur->defense / 2;
    if(joueur->niveau_fatigue > 0){
        joueur->niveau_fatigue -= 1;
    }
}

void repos(Plongeur* joueur){
    //redonne deux points de fatigue (baisse la fatigue)
    if(joueur->niveau_fatigue > 1){
        joueur->niveau_fatigue -= 2;
    } else {
        joueur->niveau_fatigue = 0;
    }
}

FinDeTour ouvrirInventaire(Plongeur* joueur, CreatureMarine* creature){
    return PAS_FIN_DE_TOUR;
}

int utiliserObjet(Plongeur* joueur, CreatureMarine* creature){
    return FIN_DE_TOUR;
}

EtatFuite fuir(int chanceFuite){
    
    int tirage = rand() % 100;
    printf("Chance de fuite : %d%%, Tirage : %d\n", chanceFuite, tirage);

    if (tirage < chanceFuite) {

        printf("Fuite reussie !\n");
        return FUITE_REUSSIE;

    } else {

        printf("Fuite echouee !\n");
        return FUITE_ECHOUEEE;

    }
}

void ouvrirBestiaire(){

}