#ifndef _TERRAIN_H_
#define _TERRAIN_H_

/*
 * Definitions des constantes 
 */

#define TERRAIN_TAILLE_CASE sizeof(char)
#define TERRAIN_TAILLE_ENTETE (sizeof(int)*2)
#define TERRAIN_CASE_LIBRE ' ' 

/*
 *  Definition des structures
 */


/*
 * Primitives de terrain 
 */

/* Definition d'une cellule tableau/fichier */

typedef struct coord_s
{
     int x ;		/* abscisse case : # colonne */
     int y ;		/* ordonnee case : # ligne */
     off_t pos ;	/* position dans le fichier */
} coord_t ;

/* Definition d'une case dans le fichier */

typedef char case_t ;

/* 
 * Affichage du terrain
 */

extern int terrain_afficher( const int ); /* Descripteur fichier terrain */


/* 
 * Initialisation du terrain 
 */

extern int terrain_initialiser( const char *,	/* Reference du fichier terrain */
				int,		/* Nb lignes   */
				int) ;		/* Nb colonnes */

/*
 * Recherche des cases voisines d'une case[y,x] dans le terrain 
 */

extern
int 
terrain_voisins_rechercher( const int,	  /* descripteur fichier terrain */
			    const coord_t,/* Coordonnees case */
			    coord_t **,   /* liste des coordonnees des cases voisines */
			    int * ) ;     /* nb de voisins dans la liste */

/* 
 * Choix aleatoire d'une case libre parmi une liste de voisins
 * Resultat dans <ind_case_libre> . Si il n'existe pas de cases
 * libres alors <ind_case_libre> est egal a -1.
 */

extern 
int
terrain_case_libre_rechercher( const int,	/* Descripteur fichier terrain */
			       coord_t * const,	/* Liste des voisins */
			       const int,	/* Nombre de voisins dans la liste */
			       int * );		/* Indice d'une case voisine libre */

/* 
 * Ecriture de <marque> a la position <position> dans <fd>
 */

extern
int 
terrain_marque_ecrire( const int,	/* fd fichier terrain */
		       const coord_t,	/* coordonnees : [x,y] + position */
		       const case_t) ;	/* marque */

/* 
 * Affichage d'une liste de cases voisines
 */

extern 
int
terrain_voisins_afficher( const int,		/* Descripteur du fichier terrain */
			  coord_t * const,	/*  Liste des voisins  */
			  const int ) ;		/* Nombre de voisins */

/* 
 * Lecture des dimensions du terrain
 */

extern 
int
terrain_dim_lire( const int,	/* descripteur fichier terrain */
		  int * ,	/* nombre de lignes */
		  int * );	/* nombre de colonnes */

/*
 * Conversion de coordonnees [x,y] en position dans le fichier
 */

extern
int
terrain_xy2pos( const int,	/* descripteur fichier terrain */
		const int,	/* abscisse dans le tableau terrain */  
		const int,	/* ordonnee dans le tableau terrain */
		off_t * );	/* position dans le fichier terrain */


/*
 * Conversion d'une position dans le fichier en coordonnees [x,y]
 */

extern
int
terrain_pos2xy( const int,	/* descripteur fichier terrain */
		const off_t,	/* position dans le fichier terrain */
		int *,		/* abscisse dans le tableau terrain */  
		int *);		/* ordonnee dans le tableau terrain */

/*
 * Lecture d'une case du terrain
 */ 

extern 
int 
terrain_case_lire( const int,		/* descripteur du fichier terrain */
		   const coord_t,	/* coordonnees de la case a lire */
		   case_t * );		/* contenu de la case a lire */
#endif

