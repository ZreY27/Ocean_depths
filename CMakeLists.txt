cmake_minimum_required(VERSION 3.26)
project(OceanDepths C)

set(CMAKE_C_STANDARD 11)

# Déclare l'exécutable + toutes les sources .c
add_executable(OceanDepths
    __test.c
    code/src/affichage.c
    code/src/carte.c
    code/src/combat.c
    code/src/creatures.c
    code/src/inventaire.c
    code/src/joueur.c
    code/src/sauvegarde.c
    code/src/console_utils.c
)

# Dossiers d'en-têtes (.h)
target_include_directories(OceanDepths PRIVATE
    code/include
)