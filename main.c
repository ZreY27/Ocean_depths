#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code/include/affichage.h"
#include "code/include/joueur.h"
#include "code/include/creatures.h"
#include "code/include/carte.h"
#include "code/include/sauvegarde.h"
#include "code/include/console_utils.h"
#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep(x)
#else
#include <unistd.h>
#endif


int main(void) {
    srand(time(NULL)); // Initialisation de la graine pour les nombres aléatoires
    initConsole();
    Plongeur joueur = initJoueur();
    CreatureMarine kraken = initCreature();
    Carte carte = initCarte(10, 10);
    int entree_utilisateur = 0;
    while (entree_utilisateur != 3)
    {
        afficherMenuPrincipal();
        scanf("%d", &entree_utilisateur); // Attente d'une entrée utilisateur pour continuer
        switch (entree_utilisateur){
            case 1 : {
                int valide = 0;
                while (!valide) {
                    sauvegarde(joueur, carte, "../code/saves/carteSaveTest.txt");
                    nettoyerAffichage();
                    afficherCarte(carte);
                    afficherJoueurStat(&joueur);
                    valide = deplacement(&joueur, carte);
                }
            }
            break;
            case 2 : {
                printf("Fonctionnalité de chargement non encore implémentée.\n");
            }
            break;
            default :
                break;
        }
        nettoyerAffichage();
    }
    return 0;
}