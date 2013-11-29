#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int
main( int nb_arg , char * tab_arg[] )
{

     char nomprog[128] ;
     char fich_vers[128] ;

     int fd_vers ;

     char mess[128] ;
     int nb_vers = 0 ;
     pid_t pid_aire = 0 ;

     /*--------------------*/

     if( nb_arg != 2)
     {
	  fprintf(stderr, "Usage %s <fichier vers>\n",
		  tab_arg[0] );
	  exit(-1);
     }


     strcpy( nomprog      , tab_arg[0] );
     strcpy( fich_vers    , tab_arg[1] );

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fich_vers , O_WRONLY | O_CREAT | O_TRUNC , 0666)) == -1 )
     {
	  sprintf( mess, "%s : Pb open sur %s", nomprog , fich_vers);
	  perror(mess);
	  exit(-1);
     }

     /* 
      * Ecriture de la ligne d'entete
      */

     if( write( fd_vers , &nb_vers , sizeof(int)) == -1 )
     {
	  perror( "Pb write sur ecriture nb_vers");
	  exit(-1);
     }

     if( write( fd_vers , &pid_aire , sizeof(pid_t)) == -1 )
     {
	  perror( "Pb write sur ecriture pid aire");
	  exit(-1) ;
     }

     /*
      * Fermeture fichier des vers 
      */

     close(fd_vers) ;
     
     exit(0);

}
