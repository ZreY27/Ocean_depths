#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "creatures.h"
#include "joueur.h"
#include "carte.h"

typedef enum{
    AFFICHAGE_LENT,
    AFFICHAGE_NORMAL,
    AFFICHAGE_RAPIDE
} EtatAffichage;

void afficherCombat(const CreatureMarine * creature, const Plongeur * joueur, 
    const char* message, const char* menu, EtatAffichage etat_affichage); // Faite
void afficherBarrePV(int pv_actuels, int pv_max, int longueur); // Faite
void afficherBarrePA(int pa_actuels, int pa_max, int longueur); // Faite
void afficherStatuts(int est_empoisonne, int est_etourdi, int niveau_fatigue); // Faite
void afficherJauge(const char* label, int valeur_actuelle, int valeur_max); // Faite

void afficherInventaire(Inventaire* inventaire); // Faite

void afficherCarte(Carte carte); 

void afficherJoueurStat(Plongeur * joueur);
void nettoyerAffichage(); // Faite


#endif