#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>


ver_t ver;

/*
 * HANDLERS
 */
void handler_debut(int s){

    printf("\n Le ver %c se lance dans la partie\n", ver.marque);
}

void handler_fin(int s){

    printf("\nLe ver %c est éliminé\n", ver.marque);
}

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;
     char fich_terrain[128] ;
     char fich_vers[128] ;
     case_t marque ;
     int signal ;
     pid_t pid_aire ;
     int noerr ;
     unsigned int t ;
     int fd_vers;


     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 5 )
     {
	  fprintf( stderr , "Usage : %s <marque> <signal> <fichier terrain> <fichier vers>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     /* Nom du programme */
     strcpy( nomprog , tab_arg[0] );

     /* Marque du ver */
     if( strlen(tab_arg[1]) !=1 ) 
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   nomprog , tab_arg[1] );
	  exit(-1) ;
     }
     marque = tab_arg[1][0] ;
 
     /* References des fichiers terrain et vers */
     strcpy( fich_terrain , tab_arg[3] );
     strcpy( fich_vers , tab_arg[4] );

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     /*Initialisation des valeurs du ver*/
     ver.marque = marque;
     ver.pid = getpid();
     ver.sig = atoi(tab_arg[2]);

     /*On redirige le signal SIGUSR1, qui indiquera que le processus aire a lancé le jeu*/
     struct sigaction v_action;
     v_action.sa_handler = handler_debut;
     v_action.sa_flags = SA_RESTART;
     sigemptyset(&v_action.sa_mask);
     sigaction(SIGUSR1, &v_action, NULL);

     /*On redirige le signal SIGQUIT, qui signifiera la fin du ver*/
     v_action.sa_handler = handler_fin;
     

     /*
      * On crée un verrou sur le fichier des vers le temps qu'il s'inscrive dedans.*/
     struct flock verrou;
     verrou.l_type = F_WRLCK;
     verrou.l_whence = SEEK_SET;
     verrou.l_start = 0;
     verrou.l_len = 0;

     /*On pose le verrou*/
     if((fd_vers = open(fich_vers, O_RDWR, 0666)) ==-1){

         fprintf(stderr, "%s : erreur dans l'ouverture de : %s\n", nomprog, fich_vers);
         exit(-1);
     }

     fcntl(fd_vers, F_SETLKW, verrou);
     
    /*On ajoute le ver au fichier des vers*/
     vers_fichier_ajouter(fich_vers, ver);

     /* On lit le pid de l'aire*/
     if((noerr = vers_fichier_aire_lire(fich_vers, &pid_aire))==-1){

         fprintf(stderr, "%s : erreur dans vers_fichier_aire_lire\n", nomprog);
         exit(noerr);
     }
     /*On lève le verrou*/
     verrou.l_type = F_UNLCK;
     fcntl(fd_vers, F_SETLKW, verrou);

     /*On ferme le fichier des vers dont on a plus besoin désormais*/
     close(fd_vers);

     /*On affiche que le ver a été inscrit au fichier ver*/
     printf("\n\n le ver %c (%d) [%d] est inscrit au fichier des vers\n\n", ver.marque, ver.pid, ver.sig);

     /*On envoie le signal SIGUSR1 pour signaler au processus aire l'ajout d'un ver au fichier*/
     kill(pid_aire, SIGUSR1);

     /*On attend que aire ai lancé sa boucle*/
     sleep(random() % TEMPS_COURT);

     while(1){

         sleep(random() % TEMPS_COURT);
         kill(pid_aire, ver.sig);
     }

     printf( "\n\n--- Arret ver %c (%d) [%d] ---\n\n" ,
	     ver.marque , ver.pid , ver.sig );
  
     exit(0);
}
