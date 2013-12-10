#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <msg_messages.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     int i;
     int id_bal;
     message_t envoi;
     struct timeval debut, fin, temps;
     float duree, debut_transmission;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Emetteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/

     /*recuperation de l identifiant de la BAL*/

     if( (id_bal = msgget(CLE_BAL, 0666)) == -1){

          fprintf(stderr, "%s : Erreur dans la recuperation de l identifiant de la boite aux lettres\n\n", nomprog);
          exit(-1);
     
     }/*fin du if*/

     /*remplissage du message a envoyer*/

     msg_remplir(&envoi, 'b');

     printf("Debut de l emission\n");

     if( (gettimeofday(&debut, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps avant emission\n\n", nomprog);
          exit(-1);

     }/*Fin du if*/

     /*Boucle d envoi de messages au recepteur*/

     for(i = 0; i < MESSAGES_NB; i ++){

          if( (msgsnd(id_bal, &envoi, sizeof(corps_t), 0)) == -1){

               fprintf(stderr, "%s : Erreur lors de l envoi du message %d\n\n", nomprog, (i+1));
               exit(-1);
          
          }/*Fin du if*/
     
     }/*fin du for*/
     
     /*Recuperation du temps apres reception des messages*/

     if( (gettimeofday(&fin, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps apres emission\n\n", nomprog);
          exit(-1);

     }/*Fin du if*/

     /*Recuperation de la duree d emission du temps et affichage*/

     timersub(&fin, &debut, &temps);
     duree = temps.tv_sec + (temps.tv_usec * 1e-6);

     printf("Fin de l emission\n");

     /*Envoi de la date de debut d emission*/

     debut_transmission = debut.tv_sec + (debut.tv_usec * 1e-6);
     sprintf(envoi.corps.buffer, "%f", debut_transmission);
     if( (msgsnd(id_bal, &envoi, sizeof(corps_t), 0)) == -1){

               fprintf(stderr, "%s : Erreur lors de l envoi du message de date de transmission\n\n", nomprog);
               exit(-1);
     
     }/*Fin du if*/


     printf("La duree pour l emission de %d mesages de taille %d est : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree);
     
     /*transmission de la date de debut d emission pour calcul de duree de transmission*/

     //if( (

     exit(0);
}
