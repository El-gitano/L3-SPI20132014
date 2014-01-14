#include <stdio.h>
#include <stdlib.h>
#include <messages.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char * argv[]){

     /*Recupération des arguments*/
     char nomprog[128];
     int CLE_EX;

     if(argc != 2){

          fprintf(stderr, "Usage : %s <Cle externe>\n", argv[0]);
          return EXIT_FAILURE;
     }
     
     strcpy(nomprog, argv[0]);
     CLE_EX = atoi(argv[1]);

     /*Fin de la récupération*/

     /*récupération de l'identifiant de la BAL*/
     
     int id_bal;

     if( (id_bal = msgget(CLE_EX, 0666)) == -1){

          fprintf(stderr, "%s : Problème dans la recherche de la BAL\n", nomprog);
          exit(-1);
     }


     /*Création de la demande au PC course*/

     requete_t demande;
     demande.type = PC_COURSE;
     demande.corps.dossard = getpid();

     /*Creation de la structure pour accueillir le retour du PC Course*/

     reponse_t resultat;

     /*Preparation a la course*/
    
     messages_initialiser_attente();

     /*Debut de la course*/

     do {
          /*Attente entre deux tours de la course*/
          messages_attendre_tour();
          
          /*Envoi du message*/
          if( (msgsnd(CLE_EX, &demande, sizeof(corps_requete_t), 0)) == -1){

               fprintf(stderr, "%s : Probleme rencontre lors de l'envoi du message au PC Course\n", nomprog);
               exit(-1);
          }

          /*Reception de la reponse*/
          if( (msgrcv(CLE_EX, &resultat, sizeof(corps_reponse_t), demande.corps.dossard, 0)) == -1){

               fprintf(stderr, "%s : Probleme lors de la recuperation de la reponse du PC Course\n", nomprog);
               exit(-1);
          }

          /*Affichage de la reponse du PC Course*/

          messages_afficher_reponse(&resultat);
     }while(resultat.corps.etat == EN_COURSE);

     /*Affichage du resultat à la fin*/

     switch(resultat.corps.etat){

          case ARRIVE :
               printf("Le coureur %d a finalement franchi la ligne d'arrivée\n", getpid());
               break;

          case DECANILLE :
               printf("Le coureur %d a succombé pendant la course\n", getpid());
               break;

          default :
               printf("Qu'est il arrivé du coureur %d?\n", getpid());
               break;
     }

     return EXIT_SUCCESS;
}
