#ifndef COMBAT_H
#define COMBAT_H

typedef enum {
    AUCUNE_ACTION,
    ACTION_JOUEUR,
    ACTION_CREATURE,
    ACTION_DOUBLE
} EtatAction;

typedef enum{
    FUITE_ECHOUEEE,
    FUITE_REUSSIE
} EtatFuite;

#endif