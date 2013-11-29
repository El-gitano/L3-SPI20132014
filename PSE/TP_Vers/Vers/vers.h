#ifndef _VERS_H_
#define _VERS_H_

#include <commun.h>
#include <terrain.h>
#include <unistd.h>


#define MAX_VERS  8

typedef struct ver_s
{
     coord_t   tete ;
     case_t    marque ;
     pid_t     pid ;
     int       sig ;
     booleen_t actif ;
} ver_t ;

/* 
 * Affichage d'un ver
 */

extern
void
vers_afficher( FILE * const,	/* Canal d'affichage */
	       const ver_t );	/* Ver a afficher */


/* 
 * Transformation d'un numero de signal en numero de ver 
 */

extern  
int
vers_sig2ind( const int,	/* signal */
	      ver_t * const,	/* liste des vers */
	      const int ) ;	/* nombre de vers dans la liste */ 


/*
 * Affichage de la liste des vers 
 */

extern  
void
vers_liste_afficher( ver_t * const,	/* liste des vers */
		     const int) ;	/* nombre de vers dans la liste */ 


/*
 *  Teste si il y a au plus un ver dans le terrain
 */ 

extern
booleen_t
vers_liste_dernier( ver_t * const,	/* liste des vers */
		    const int,		/* nombre de vers dans la liste */ 
		    int * );		/* indice du dernier ver */

/*
 *  Teste si il n'y a plus de vers actifs
 *  Renvoie VRAI si il y a au moins un vers actif
 *          FAUX sinon
 */ 

extern
booleen_t
vers_liste_actifs( ver_t * const,	/* liste des vers */
		   const int );	/* nombre de vers dans la liste */


/* 
 * Chargement d'une liste de vers a partir d'un fichier de sauvegarde
 * Format du fichier : 
 * <nombre N de vers> 
 * <structure ver 1>
 * <structure ver 2>
 * ........
 * <structure ver N>
 *
 */

extern
int
vers_liste_charger( char * const,	/* Reference fichier de sauvegarde des vers */
		    ver_t **,		/* Liste des vers */
		    int * );		/* Nombre de vers dans la liste */

/* 
 * Ajout d'un ver dans un fichier de vers 
 */

extern 
int
vers_fichier_ajouter( char * const,	/* Reference fichier vers */
		      const ver_t );	/* Ver a ajouter */


/* 
 * Ecriture du pid de l'aire dans le fichier des vers
 */

extern 
int
vers_fichier_aire_ecrire( char * const,	/* Reference fichier vers */
			   const pid_t);	/* Pid a ecrire */

/* 
 * Lecture du pid de l'aire dans le fichier des vers
 */

extern 
int
vers_fichier_aire_lire( char * const,	/* Reference fichier vers */
			pid_t * );	/* Pid a lire */

/* 
 * Affichage d'un fichier de vers                      
 */

extern
int
vers_fichier_afficher( char * const )	; /* Reference fichier vers */


/*
 * Initialisation d'un fichier de vers 
 */

extern 
int
vers_fichier_initialiser( char * const ) ;	/* Reference du fichier des vers */ 

#endif


