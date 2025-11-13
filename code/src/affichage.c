#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/affichage.h"
#include "../include/creatures.h"
#include "../include/joueur.h"
#include "../include/carte.h"
#include "../include/inventaire.h"

#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep(x)
#else
#include <unistd.h>
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

void afficherInventaire(Inventaire* inventaire) {
    printf("🎒  INVENTAIRE  🎒\n");
    char message[512] = "";
    stringInventaire(inventaire, message);
    printf("%s\n", message);    
}

// ✅ barre de PV améliorée
void afficherBarrePV(int pv_actuels, int pv_max, int longueur) {
    int nb_blocs = (pv_actuels * longueur) / pv_max;
    printf("[");
    for (int i = 0; i < longueur; i++) {
        if (i < nb_blocs)
            printf(GREEN "█" RESET);
        else
            printf(RED "░" RESET);
    }
    printf("] %3d/%3d", pv_actuels, pv_max);
}

// ✅ nouvelle barre pour les points d’action (ATB)
void afficherBarrePA(int points_action, int seuil_action, int longueur) {
    int nb_blocs = (points_action * longueur) / seuil_action;
    printf("[");
    for (int i = 0; i < longueur; i++) {
        if (i < nb_blocs)
            printf(CYAN "■" RESET);
        else
            printf("·");
    }
    printf("] %d/%d", points_action, seuil_action);
}

// ✅ petite fonction utilitaire pour les statuts
void afficherStatuts(int est_empoisonne, int est_etourdi, int niveau_fatigue) {
    if (est_empoisonne) printf(" ☠️ ");
    if (est_etourdi) printf(" 💫 ");
    if (niveau_fatigue > 0) {
        printf(" 😴x%d", niveau_fatigue);
    }
}

// ✅ fonction principale d’affichage
void afficherCombat(const CreatureMarine* creature, const Plongeur* joueur,
                    const char* message, const char* menu, EtatAffichage etat_affichage) {
    system("clear || cls"); // nettoyage cross-platform
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                      🌊  OCEAN DEPTHS  🌊                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    // === Bloc supérieur : Créature ===
    printf(BOLD "%-25s" RESET "\nHP: ", creature->nom);
    afficherBarrePV(creature->points_de_vie_actuels, creature->points_de_vie_max, 20);
    printf("  |  Fatigue: %d/4  |  Vitesse: %d\n", creature->niveau_fatigue, 
            creature->vitesse);

    printf("   Points d'action : ");
    afficherBarrePA(creature->points_action, 100, 20);
    printf("  Statuts: ");
    afficherStatuts(creature->est_empoisonne, creature->est_etourdi, creature->niveau_fatigue);
    printf("\n\n");

    // === VS centré ===
    printf("%33s\n\n", "⚔️  VS  ⚔️");

    // === Bloc inférieur : Joueur ===
    printf(BOLD "%-25s" RESET "\nHP: ", "Plongeur");
    afficherBarrePV(joueur->points_de_vie_actuels, joueur->points_de_vie_max, 20);
    printf("  |  Fatigue: %d/4  |  Vitesse: %d\n", joueur->niveau_fatigue,
            joueur->vitesse);

    printf("   Points d'action : ");
    afficherBarrePA(joueur->points_action, 100, 20);
    printf("  Statuts: ");
    afficherStatuts(joueur->est_empoisonne, joueur->est_etourdi, joueur->niveau_fatigue);
    printf("\n");

    // === Message dynamique ===
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    const char* debut = message;
    const char* fin;
    while ((fin = strchr(debut, '\n')) != NULL) {
        printf("║ %-62.*s ║\n", (int)(fin - debut), debut);
        debut = fin + 1;
    }
    printf("║ %-62s ║\n", debut);
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    // === Menu des actions ===
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    debut = menu;
    while ((fin = strchr(debut, '\n')) != NULL) {
        printf("║ %-62.*s ║\n", (int)(fin - debut), debut);
        debut = fin + 1;
    }
    printf("║ %-62s ║\n", debut);
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    if(etat_affichage == AFFICHAGE_LENT){
        usleep(1750);
    }
    else if (etat_affichage == AFFICHAGE_NORMAL){
        usleep(1000);
    }
    else {
        usleep(100);
    }
    
}

void afficherCarte(Carte carte) {
    for (int i = 0; i < carte.hauteur; i++) {
        for (int j = 0; j < carte.longueur; j++) {

            if (carte.cases[i][j].joueur == 1) {
                printf("🤿 "); // position du joueur
            }
            else if (carte.cases[i][j].visible == 0) {
                printf("⬛ "); // zone non explorée
            }
            else {
                printf("%s ", getEmojiForType(carte.cases[i][j].type));
            }
        }
        printf("\n");
    }

    printf("\n");
}

void afficherJauge(const char* label, int valeur, int max) {
    int largeur = 20; // longueur de la barre
    int nbBloc = (valeur * largeur) / max;

    printf("%-10s [", label);
    for (int i = 0; i < largeur; i++) {
        if (i < nbBloc) printf("#");
        else printf("-");
    }
    printf("] %d/%d\n", valeur, max);
}

void afficherJoueurStat(Plongeur *joueur) {
    printf("\n===== STATS DU PLONGEUR =====\n");

    afficherJauge("❤️ Vie", joueur->points_de_vie_actuels, joueur->points_de_vie_max);
    afficherJauge("💧 Oxygène", joueur->niveau_oxygene, joueur->niveau_oxygene_max);

    printf("😴 Fatigue : %d / 5\n", joueur->niveau_fatigue);
    printf("💎 Perles  : %d\n", joueur->perles);

    printf("=============================\n\n");

    afficherInventaire(&joueur->inventaire);
}

void nettoyerAffichage() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}