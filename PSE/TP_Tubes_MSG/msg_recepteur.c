#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>

int id_bal;

void hand_arret(int sig){

     msgctl(id_bal, IPC_RMID, 0);
     printf("Destruction de la Boite aux Lettres\n");
     exit(0);
}

int 
main( int nb_arg , char * tab_arg[] ){

     char nomprog[128] ;
     message_t recu;
     int i;
     struct timeval debut, fin, temps;
     float duree , duree_transmission, debut_transmission, fin_transmission;

     /*-----*/

     if( nb_arg !=1 ){

	     fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
	     fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	     exit(-1);
     }
     strcpy( nomprog , tab_arg[0] );

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/

     /*Creation de la boite aux lettres*/

     if( (id_bal = msgget(CLE_BAL, IPC_CREAT | IPC_EXCL | 0666)) == -1){

          fprintf(stderr, "%s : Erreur lors de la creation de la Boite aux lettres\n\n", nomprog);
          exit(-1);
     
     }/*Fin du if*/

     printf("Debut de la reception\n");

     /*Recuperation du temps avant la reception*/

     if( (gettimeofday(&debut, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps avant reception\n\n", nomprog);
          exit(-1);

     }/*Fin du if*/

     /*Boucle de reception des messages*/

     for(i = 0; i < MESSAGES_NB; i ++){

          /*Attente de la recuperation d un message*/

          if( ( msgrcv(id_bal, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0)) == -1){

               fprintf(stderr, "%s : Erreur lors de la reception d un message\n\n", nomprog);
               exit(-1);
          
          }/*Fin du if*/

          //msg_afficher(&recu);

     }    /*Fin du for*/

     /*Recuperation du temps apres reception des messages*/

     if( (gettimeofday(&fin, NULL)) == -1){

          fprintf(stderr, "%s : Erreur lors de la recuperation du temps apres reception\n\n", nomprog);
          exit(-1);

     }/*Fin du if*/

     /*Recuperation de la duree de reception du temps et affichage*/

     timersub(&fin, &debut, &temps);
     duree = temps.tv_sec + (temps.tv_usec * 1e-6);

     printf("Fin de la reception\n");

     /*reception de la date de debut d emission*/
     if( ( msgrcv(id_bal, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0)) == -1){

               fprintf(stderr, "%s : Erreur lors de la reception d un message\n\n", nomprog);
               exit(-1);
     }/*Fin du if*/

     /*Transformation du corps du message en duree*/
     debut_transmission = strtod(recu.corps.buffer, NULL);

     /*Calcul de la duree de transmission*/
     fin_transmission = fin.tv_sec + (fin.tv_usec * 1e-6);
     duree_transmission = fin_transmission - debut_transmission;

     printf("La duree pour la reception de %d mesages de taille %d est : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree);
     printf("La duree pour la transmission de %d messages de tailles %d est : %.3f secondes\n\n", MESSAGES_NB, MESSAGES_TAILLE, duree_transmission);

     /*Suppression de la boite aux lettres*/
     if( (msgctl(id_bal, IPC_RMID, 0)) == -1){

          fprintf(stderr, "%s : Erreur lors de la suprression de la la Boite aux Lettres", nomprog);
          exit(-1);

     }/*Fin du if*/
     
     exit(0);
}/*Fin du main*/
