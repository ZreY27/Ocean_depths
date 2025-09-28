cmake_minimum_required(VERSION 3.26)
project(OceanDepths C)

set(CMAKE_C_STANDARD 11)

# Déclare l'exécutable + TOUTES les sources .c qui contiennent tes fonctions
add_executable(OceanDepths
        main.c
        code/src/affichage.c
        code/src/joueur.c
        code/src/creatures.c
        code/src/carte.c
)

# Dossiers d'en-têtes (.h)
target_include_directories(OceanDepths PRIVATE
        code/include
)
