/*TD de synthese du 14/11/2013
 * Made In Sweetzerland
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define CLE 1
#define SCRUTE 11
#define ATTENTE 20
int id_bal;

typedef struct flux_s{

     int nb_imp;
     int nb_ecr;
} flux_t;

typedef struct message_s{

     long type;
     flux_t corps;
}message_t;


int main(){

     int tube1[2], tube2[2];
     char c;
     flux_t envoyes;
     message_t demande;
     envoyes.nb_imp = 0;
     envoyes.nb_ecr = 0;

     
     if(pipe(tube1) || pipe(tube2)){

        perror("pb sur la creation du tube 1\n");
        exit(-1);
     }

     switch(fork()){

          case -1 :    //Cas d'erreur de creation du processus
                      
               perror("Pb fork\n");
               exit(-1);
          
          case 0 :     //Fils imprimante

                     close(tube1[1]);   //on ferme l'entrée écriture du tube1 car le fils0 n'écrit pas dans le tube
                     
                     
                     close(tube2[0]);   //Puisque le fils O ne lit pas dans tube 2, on ferme l'accès lecture du tube 2

                     close(tube2[1]);   //On ferme l'accès en écriture au tube 2

                     FILE *fich;
                     int fd_trace;

                     if((fich = fopen("trace", "wr"))== NULL){
                          perror("Problème d'ouverture du fichier trace dans l'imprimante\n");
                          exit(-1);
                     }
                     
                     while(read(tube1[0], &c, 1)) {
                          
                          fwrite(&c, sizeof(char), 1, fich);
                     }

                     fclose(fich);
                     close(tube1[0]);
                     break;
          
          default :
                     switch(fork()){
                          
                         case -1 :    //Cas d'erreur de creation du processus
                               
                               perror("Pb fork\n");
                               exit(-1);
                         
                         case 0:

                               close(tube1[0]);
                               close(tube1[1]);
                               close(tube2[1]);

                               while(read(tube2[0], &c, 1)){

                                    printf("%c ", c);
                               }

                               close(tube2[0]);

                         default :

                               close(tube2[0]);
                               close(tube1[0]);

                               while((c = getchar()) !=EOF){

                                    if( c == '+'){

                                         while((c=getchar()) != '%'){

                                              write(tube1[1], &c, 1);
                                              envoyes.nb_imp ++;
                                         }
                                    }
                                    if(c == '*'){

                                         while((c =getchar()) !='%'){

                                              write(tube2[1], &c, 1);
                                              envoyes.nb_ecr ++;
                                         }
                                    }
                               }

                               int id_bale = msgget(CLE, 0666);
                               demande.type = SCRUTE;
                               demande.corps.nb_imp = envoyes.nb_imp;
                               demande.corps.nb_ecr = envoyes.nb_ecr;
                               msgsnd(id_bale, &demande, sizeof(demande.corps), 0);
                               close(tube1[1]);
                               close(tube2[1]);
                               break;
                     }
     }
     return EXIT_SUCCESS;
}

void hand_int(int s){
     printf("La Boite Au lettre va être détruite\n");
     msgctl(CLE, IPC_RMIND);
     exit(0);
}

void hand_quit(int s){

     message_t m;
     printf("La boite au lettre va être vidée");
     while((msgrcv(id_bal, &m, sizeof(flux_t), SCRUTE, IPC_NOWAIT)) != -1 && (erno != ENOMSG));

}

int scrute(){

     id_bal = msgget(CLE, 0666,| IPC_CREATE| O_EXCC);
     message_t m;
     int somme_imp =0, somme_ecr =0, nbre = 0;

     signal(SIGINT, hand_int);
     signal(SIGQUIT, hand_quit);

     while(1){
          msgrcv(id_bal, &m, sizeof(m.corps), SCRUTE, 1, 0);
          somme_imp += m.corps.nb_imp;
          somme_ecr += m.corps.nb_ecr;
          nbre ++;
          printf("Nombre de caractère envoyés :\n-à l'imprimante : %d\n-à l'écran : %d\n", m.corps.nb_imp, m.corps.nb_ecr);
          printf("Moyenne imprimante = %f\n moyenne ecran = %f\n", (float)somme_imp/nbre, (float)somme_ecr/nbre); 
     }

     return EXIT_SUCCESS;
}
