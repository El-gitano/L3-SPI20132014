#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[] )
{
     
     char nomprog[128] ;
     char message[MESSAGES_TAILLE] ; 

     struct timeval temps ;   
     double temps_debut;
     double temps_fin;

     /*----------*/

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "Role  : Test des fonctions de messages pour un Tube\n");
	  fprintf( stderr , "Usage : %s \n", tab_arg[0] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );

     printf( "\n---------- Debut %s ----------\n" , nomprog ) ; 

     gettimeofday(&temps, NULL);  
     temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);  

     printf("Remplissage du message avec des X\n"); 
     pipe_remplir( message , 'X') ;

     printf( "Affichage du message\n"); 
     pipe_afficher( message );

     gettimeofday(&temps, NULL);  
     temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);  
     
     printf("\nTemps d'execution du programme %s =  %.6lf secondes  !!!\n", nomprog , temps_fin - temps_debut);  
     
     printf( "\n----------- Fin %s -----------\n" , nomprog ) ; 
  
     exit(0);

}
