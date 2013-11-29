#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define K_MAX 10000
#define N_MAX 1000

int max(int a, int b){        /*Fonction de comparaison pour qsort*/

     if(a > b)
          return 1;
     
     if (a == b)
          return 0;
     else
          return -1;
}

struct timeval chrono(){       /*Fonction renvoyant un nombre de microsecondes*/

     struct timeval t;
     gettimeofday(&t, NULL);
     //fprintf(stderr, "\nsec = %d, microsec = %d\n", t.tv_sec, t.tv_usec);
     return (t);
}

int main(int argc, char * argv[]){

     /*Recupération des arguments*/
     if(argc < 4 || (atoi(argv[1]) > K_MAX) || (atoi(argv[3]) > N_MAX)){

          printf("Usage : %s <nombre d'execution> <commande> <nombre de fils>\navec : <nombre d'execution> < %d et <nombre de fils> < %d\n", argv[0], K_MAX, N_MAX);
          exit(-1);
     }


     /*Variables utilisées par les fils et le père*/
     int tube[2], i =0, j = 0, fd;
     struct timeval debut, fin, temps;
     long int duree;
     int cr, ret;        /*Compte rendu des fils et petits-fils*/

     char nomprog[128];
     char commande[128];
     char **argscommande;
     strcpy(nomprog, argv[0]);
     strncpy(commande, argv[2], sizeof(commande));         /*Correspond à C*/
     int nbre_exec = atoi(argv[1]);     /*Correspond à K*/
     int nbre_fils = atoi(argv[argc -1]);     /*Correspond à N*/
     /*fprintf(stderr, "Nombre de fils : %d\n", nbre_fils);*/


     /*Variables utilisées par le père*/
     long int *tab = (long int *)malloc(sizeof(long int)*nbre_fils);
  
     
     /*recuperation des arguments de la commande*/
     /*if(argc > 4){
          argscommande = (char **)malloc(sizeof(char *)*(argc-3));
          int nbrarg = 0;
          for(i = 2; i < argc-1; i ++){
               argscommande[nbrarg] =(char *)malloc(strlen(argv[i])+1);
               strcpy(argscommande[nbrarg], argv[i]);
               nbrarg++;
          }
	  argscommande[nbrarg] = NULL;
     }*/

     if(pipe(tube)){

          fprintf(stderr, "%s : erreur dans la creation du tube\n", nomprog);
          exit(-1);
     }

     for(i = 0; i < nbre_fils; i++){

          switch(fork()){

               case -1:       /*Cas d'erreur*/
                    fprintf(stderr,"%s : erreur dans le fork n°%d\n", nomprog, i);
                    exit(-1);

               case 0:
                    /*
                     * Fils numero i
                     */

                    close(tube[0]);     /*Fermeture de l entree lecture du tube*/

                    debut = chrono();   /*Recuperation d un nombre de microsecondes avant les executions de la commande*/

                    for(j = 0; j < nbre_exec; j ++){        /*Boucle de K executions de la commande*/
                         
                         fd = open("/dev/null", O_WRONLY);
                         close(1);
                         dup(fd);
                         /*Execution de C, avec en retour un valeur permettant d'être informé si la commande a ete iterrompue*/
                         ret = system(commande);                 

                         if(WIFSIGNALED(ret)){

                              fprintf(stderr, "%s interrompue par le signal %d lors de la %d eme execution par le %d eme processus\n", commande, WTERMSIG(ret), j+1, i+1);
				          #ifdef WCOREDUMP
 	      				     fprintf(stderr, "%s core a ete genere\n", WCOREDUMP(ret)? "Un":"Aucun");
				          #else
                       			fprintf(stderr, "%s core a ete genere\n", (ret & 128) == 128? "Un":"Aucun");
               			#endif
                         }
                         
                    }
		    
                    /*Recuperation du nombre de microsecondes après l'execution des K commandes*/
                    fin = chrono();

                    /*Différence entre le temps avant et le temps après l execution des commandes*/
                    timersub(&fin, &debut, &temps);

                    /*Ecriture du temps dans le tube, sous forme de microsecondes*/
                    duree = temps.tv_sec*1e6 + temps.tv_usec;

                    if(write(tube[1], &duree, sizeof(long int)) == -1){    /*Ecriture de la valeur dans le tube*/
                         
                         fprintf(stderr, "%s : erreur dans l'ecriture dans le tube par le fils %d", nomprog, i);
                         exit(-1);
                    }
                    exit(1);
          
          }
     }

     /*
      * Père
      */

     for(i = 0; i < nbre_fils; i ++){

          /*récupération du retour du fils i.*/
          if(read(tube[0], &tab[i], sizeof(long int)) == -1){
               
               perror("%s : erreur dans la lecture du tube\n");
               return EXIT_FAILURE;
          }

          if(tab[i] < 0){
               
               perror("erreur dans les donnees emises par les fils\n");
               return EXIT_FAILURE;
          }
       
          /*Calcul et affichage des donnes recuperes a la sortie du tube (temps moyen)*/
          tab[i] /= nbre_exec;

     }

     /*Tri du tableau*/
	qsort(tab, nbre_fils, sizeof(long int), max);

     /*calcul et Affichage du temps moyen*/
	long int tmpmoy = tab[nbre_fils/2];
	long int tmpmoysec = tmpmoy / 1000;
	
     printf("Le temps moyen d'execution de la commande %s est de : %ld microsecondes, soit %ld milisecondes.\nValeur trouvée pour %d execution par %d processus\n", commande, tmpmoy, tmpmoysec, nbre_exec, nbre_fils);
	free(tab);

     
     return EXIT_SUCCESS;
}
