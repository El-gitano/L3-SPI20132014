#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
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
     int fd_tube, i;
     char msg[MESSAGES_TAILLE];
     struct timeval debut, fin, temps;
     float duree;

     /*----------*/

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , tab_arg[0] );
	  fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	  exit(-1);
     }
     strcpy( nomprog , tab_arg[0] );

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/

     /*Ouverture du tube en ecriture*/

     if( (fd_tube = open(NOM, O_WRONLY, 0)) == -1){

          fprintf(stderr, "%s : erreur dans l ouverture du tube en ecriture\n\n", nomprog);
          exit(-1);

     }/*Fin du if*/

     /*Remplissage du message a envoyer*/

     pipe_remplir(msg, 'a');
     
     printf("Debut de l emission\n");

     /*Recuperation du temps avant la reception de messages*/

     if( (gettimeofday(&debut, NULL)) == -1){

          fprintf( stderr ,"%s : Erreur dans le recuperation du temps avant l emission des msgs\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     /*Ecriture dans le tube de MESSAGES_NB messages de taille MESSAGES_TAILLE*/


     for(i = 0; i < MESSAGES_NB; i ++){

          if( (write(fd_tube, msg, MESSAGES_TAILLE)) == -1){
               
               fprintf(stderr, "%s : erreur dans l ecriture du tube\n", nomprog);
               exit(-1);
          
          }/*Fin du if*/
     
     }/*Fin du for*/
     
     /*Recuperation du temps apres l emission des messages*/

     if( (gettimeofday(&fin, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps apres l emission des messages\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     /*Difference entre les temps de debut et temps de fin, et affichage du temps pour l emission*/

     timersub(&fin, &debut, &temps);

     duree = temps.tv_sec + (temps.tv_usec * 1e-6);

     /*Envoi de la date de debut de transmission*/
     if( (write(fd_tube, &debut, sizeof(debut))) == -1){

          fprintf(stderr, "%s : erreur dans l ecriture du tube\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/


     printf("Temps pour l emission de %d messages de taille %d : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree);


     printf("Fin de l emission\n\n");

     exit(0);
}
