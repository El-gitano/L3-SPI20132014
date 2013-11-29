#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>


/*
 * Initialisation de la tete d'un ver dans le terrain de jeu
 * renvoi les coordonnees d'une case libre choisie aleatoirement
 * Pour utiliser cette fonction il faut que :
 * - la structure ver soit creee
 * - la marque du ver soit affectee
 */

extern 
int jeu_ver_initialiser( const int fd_terrain, /* Fichier terrain */
			 const int nb_lig, /* dimensions terrain */
			 const int nb_col, 
			 ver_t * ver )  /* ver a initialiser */			     
{

     booleen_t trouve = FAUX ;
     case_t c = TERRAIN_CASE_LIBRE ;
     int cpt_cases = 0 ;
     int nb_cases = nb_lig * nb_col ;
     int noerr = CORRECT ;

     /*-----*/

     ver->tete.x = random() % nb_col ;
     ver->tete.y = random() % nb_lig ;
     
     while( (!trouve) && (cpt_cases<nb_cases) )
     {
	  terrain_xy2pos(fd_terrain, ver->tete.x, ver->tete.y , &(ver->tete.pos) ) ;

#ifdef _DEBUG_ 
	  printf("jeu_ver_initialiser --> examen case[%d,%d](%lld)\n", 
		 ver->tete.y , ver->tete.x , (long long)ver->tete.pos );
#endif

	  /* Lecture de la case de la position initiale */
	  if( (noerr = terrain_case_lire( fd_terrain,
					  ver->tete,
					  &c)))
	       return(noerr) ;
	  
	  /* Ecriture position initiale */
	  if( c == TERRAIN_CASE_LIBRE )
	  {
	       terrain_marque_ecrire( fd_terrain,
				      ver->tete,
				      ver->marque) ;
	       trouve = VRAI ;
	  }
	  else
	  {
	       ver->tete.x = ( ver->tete.x + 1 ) % nb_col ;
	       if(ver->tete.x == 0 ) 
	       {
		    ver->tete.y = (ver->tete.y + 1) % nb_lig ;
	       }
	       cpt_cases++ ;
	  }
     }
     
     if( trouve )
	  return(CORRECT);
     else
	  return(ERREUR);
}
