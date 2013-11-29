#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <vers.h>


int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[256] ;
     char fich_vers[128] ;

     ver_t * vers = (ver_t *)NULL ;
     int nb_vers = 0 ;

     int v ; 
     int sig ;

     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 3 )
     {
	  fprintf( stderr , "\n\n%s : envoie le signal <signal> a tous les processus vers contenus dans le fichier de reference <fichier des vers>\n\n",
		   tab_arg[0] ); 
	  fprintf( stderr , "Usage : %s <fichier des vers> <numero signal>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_vers , tab_arg[1] );
     sscanf( tab_arg[2] , "%d" , &sig ) ;
 
     printf("\n\n\t----- Debut hécatombe %s -----\n\n" , nomprog);

#ifdef _DEBUG_
     printf("Fichier des vers a tuer\n");
     vers_fichier_afficher( fich_vers );
#endif

     /* 
      *  Chargement de la liste des vers 
      */

     vers_liste_charger( fich_vers, &vers , &nb_vers );
     
     /* 
      * Envoi du signal d'arret aux vers
      */

     for( v=0 ; v < nb_vers ; v++ )
     {
	  printf("arret --> %d\n" , vers[v].pid);
	  kill(  vers[v].pid , SIGKILL );
     }
          

     printf("\n\n\t----- Fin hécatombe %s -----\n\n", nomprog);

     exit(0);
}

