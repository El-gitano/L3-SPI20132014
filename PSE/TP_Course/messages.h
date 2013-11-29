#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define PC_COURSE      1
#define MAX_COUREURS  50 
#define DISTANCE     100

#include <stdlib.h>

/* Definition des types de base */

typedef int compteur_t ;
typedef unsigned int distance_t ;
typedef enum booleen { FAUX , VRAI } booleen_t ; 

typedef enum etat_coureur { EN_COURSE , ARRIVE , DECANILLE } etat_coureur_t ;


/* Structure message Coureur --> PC Course */

typedef struct corps_requete 
{ 
  pid_t dossard ;
} corps_requete_t ; 

typedef struct requete
{
  long             type ;
  corps_requete_t corps ;
} requete_t ;

/* Structure message PC Course --> Coureur */

typedef struct coureur
{
  pid_t       dossard ;
  distance_t  distance ;
} coureur_t ;

typedef struct corps_reponse
{
  etat_coureur_t  etat ;
  compteur_t  nb_coureurs ;  
  coureur_t   tab_coureurs[MAX_COUREURS] ;
} corps_reponse_t ;

typedef struct reponse
{
  long type ;
  corps_reponse_t corps ;
} reponse_t ;


/*
 * Definition des fonctions 
 */

/* Affichage de l'etat d'un coureur */
extern
void
messages_afficher_etat( const etat_coureur_t ) ;

/* Affichage d'un message de requete d un coureur au PC Course */
extern
void
messages_afficher_requete( requete_t * const );

/* Affichage d'un message de reponse du PC Course */
extern
void
messages_afficher_reponse( reponse_t * const );

/* Affichage du parcours de la course */
extern
void
messages_afficher_parcours( reponse_t * const );

/* Initialisation de l'attente */
extern
void
messages_initialiser_attente() ;

/* Attente entre 2 envois de message vers le PC Course */
extern
void
messages_attendre_tour() ;
#endif
