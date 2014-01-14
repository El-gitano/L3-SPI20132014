#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[]){

     char nomprog[128] ;
     char msg[MESSAGES_TAILLE];
     int fd_tube, i, j;
     float duree, duree_transmission;
     struct timeval debut, fin, temps, debut_transmission, temps_transmission;

     /*-----*/

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
	  fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	  exit(-1);
     }
     strcpy( nomprog , tab_arg[0] );

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/
     /*Creation du tube*/

     if( mknod (NOM, S_IFIFO | 0666, 0) ){

          fprintf(stderr, "%s : Erreur lors de la creation du tube nommé\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     /*Ouverture du tube en lecture*/

     if( (fd_tube = open(NOM, O_RDONLY, 0) ) == -1){

          fprintf(stderr, "%s : erreur lors de l ouverture du tube nommé en lecture\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     printf("\nDebut de la reception\n");

     /*Recuperation du temps avant la reception de messages*/

     if( (gettimeofday(&debut, NULL)) == -1){

          fprintf( stderr ,"%s : Erreur dans le recuperation du temps avant la reception des msgs\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     /*Reception de MESSAGES_NB messages de taille MESSAGES_TAILLE*/

     for(i = 0; i < MESSAGES_NB; i ++){

          if( (read (fd_tube, msg, MESSAGES_TAILLE)) == -1){
               
               fprintf(stderr, "%s : erreur lors de la lecture dans le tube\n", nomprog);
               exit(-1);
          
          }/*Fin du if*/
          
     }/*Fin du for*/

     /*Recuperation du temps apres la reception des messages*/

     if( (gettimeofday(&fin, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps apres la reception des messages\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     /*Difference entre les temps de debut et temps de fin, et affichage du temps pour la reception*/

     timersub(&fin, &debut, &temps);

     duree = temps.tv_sec + (temps.tv_usec * 1e-6);

     /*Reception de la date de debut d emission/transmission*/
     if( (read (fd_tube, &debut_transmission, sizeof(debut_transmission))) == -1){
               
               fprintf(stderr, "%s : erreur lors de la lecture dans le tube\n", nomprog);
               exit(-1);
          
     }    /*Fin du if*/

     /*Calcul du temps de transmission*/
     timersub(&fin, &debut_transmission, &temps_transmission);
     duree_transmission = temps_transmission.tv_sec + (temps_transmission.tv_usec * 1e-6);

     printf("Temps pour la reception de %d messages de taille %d : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree);
     printf("Duree de la transmission de %d messages de taille %d : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree_transmission);

     /*Fermeture du tube*/

     close(fd_tube);

     exit( 0 );
}
