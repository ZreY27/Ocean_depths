#ifndef ENUM_ETAT_H
#define ENUM_ETAT_H
typedef enum{
    PAS_FIN_DE_TOUR,
    FIN_DE_TOUR
} FinDeTour;

typedef enum{
    N_EST_PAS_EMPOISONNE,
    EST_EMPOISONNE = 3
} EtatPoison;

typedef enum{
    N_EST_PAS_ETOURDI,
    EST_ETOURDI, 
    EST_LOURDEMENT_ETOURDI
} EtatEtourdi;

typedef enum{
    FUITE_ECHOUEEE,
    FUITE_REUSSIE
} EtatFuite;

#endif