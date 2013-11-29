#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <jeu.h>
#include <terrain.h>
#include <vers.h>

int
main( int nb_arg , char * tab_arg[] )
{
     int fd_terrain ;
     char fich_terrain[128] ;
     char nomprog[128] ;
     char mess[256];

     int nb_lig ;
     int nb_col ;
     booleen_t arret = FAUX ;
     int i ;
     ver_t ver ;
 
     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "%s : teste les primitives du TDA jeu\n", 
		   tab_arg[0] );
	  fprintf( stderr , "Usage : %s <fichier terrain> \n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );

     printf( "\n\n ----- Debut de %s -----\n\n ", 
	     nomprog );

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     /* 
      * Ouverture du fichier terrain 
      */
     if( ( fd_terrain = open( fich_terrain , O_RDWR , 0644 )) == -1 )
     {
	  sprintf( mess, "%s : Pb open sur %s\n", nomprog , fich_terrain);
	  perror(mess);
	  exit(-1);
     }

     /* 
      * Initialisation aleatoire des coordonnees de depart
      */

     terrain_dim_lire( fd_terrain , &nb_lig , &nb_col ) ;

     arret = FAUX ;
     i=0 ;
     while( ! arret )
     {

	  /* Affectation de la marque */
	  ver.marque = 'a' + i ;

	  /* test primitive d'initialisation d'un ver dans un terrain */
	  arret = jeu_ver_initialiser( fd_terrain, 
				       nb_lig, 
				       nb_col, 
				       &ver );  
	  i++;

	  terrain_afficher( fd_terrain );
     }

     /* 
      * Fermeture du fichier terrain 
      */ 
     close(fd_terrain); 
  
     printf( "\n\n----- Fin de %s -----\n\n ", 
	     nomprog );

     exit(0);
}
