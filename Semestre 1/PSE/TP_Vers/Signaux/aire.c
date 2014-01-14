#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>

/*
 * Variables utilisées par le handler et le main
 */
int nb_lig , nb_col ;
int fd_terrain;
ver_t * liste_vers;
int e_nbre_vers_inscrits;
int dernier = -1;
int noerr;

coord_t * liste_voisins;
int nb_voisins, ind_libre;

/*
 * HANDLERS
 */
void sig_handler_pret(int s){
    
    e_nbre_vers_inscrits ++;
}

void sig_handler_jeu(int s){

    int indice = vers_sig2ind(s, liste_vers, e_nbre_vers_inscrits);

    /*Si il ne reste plus qu'un ver actif sur le terrain, alors on lui dit de s'arreter*/
    if(vers_liste_dernier(liste_vers, e_nbre_vers_inscrits, &dernier)){

        liste_vers[dernier].actif = FAUX;
        kill(liste_vers[dernier].pid,SIGQUIT);
    }
    /*Sinon, on cherche une place pour le ver en question, et on l'y deplace si possible
     */
    else{

        /*Recherche d'une case libre*/
        if((noerr = terrain_voisins_rechercher(fd_terrain, liste_vers[indice].tete, &liste_voisins, &nb_voisins)) ==-1){
            printf("\nErreur dans terrain_voisins_rechercher\n");
            exit(noerr);
        }

        /*Choix d'une case libre parmi les voisins*/
        if((noerr = terrain_case_libre_rechercher(fd_terrain, liste_voisins, nb_voisins, &ind_libre)) == -1){

            printf("\nErreur dans terrain_case_libre_rechercher\n");
            exit(noerr);
        }

        /*S'il n'existe pas de case libre, alors le ver meurt, et on lui envoie le signal correspondant*/
        if(ind_libre == -1){

            liste_vers[indice].actif = FAUX;
            kill(liste_vers[indice].pid, SIGQUIT);
        }

        else{
            
             /*Sinon, on ecrit dans la case choisie*/
            if((noerr = terrain_marque_ecrire(fd_terrain, liste_voisins[ind_libre], liste_vers[indice].marque)) ==-1){

                printf("\nErreur dans terrain_marque_ecrire\n");
                exit(noerr);
            }
            /*On met a jour la tete du ver*/
            liste_vers[indice].tete.pos = liste_voisins[ind_libre].pos;
            liste_vers[indice].tete.x = liste_voisins[ind_libre].x;
            liste_vers[indice].tete.y = liste_voisins[ind_libre].y;


        }
        /*On affiche le terrain*/
        if((noerr = terrain_afficher(fd_terrain)) == -1){

            printf("\nErreur dans terrain_afficher\n");
            exit(noerr);
        }
        dernier = indice;
    }
}


/*
 * FONCTIONS LOCALES
 */

int
main( int nb_arg , char * tab_arg[] )
{
     char fich_terrain[128] ;
     char fich_vers[128] ;
     char mess[256];
     char Nom_Prog[256];
     int nb_vers ;
     int fd_vers;

     booleen_t init_tete = FAUX ;


     int v, w ; 
     case_t c ;
     int gagnant ;

     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 4 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <fichier des vers> <nb vers>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     strcpy( fich_vers , tab_arg[2] );
     sscanf( tab_arg[3] , "%d" , &nb_vers );



     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());
    

     e_nbre_vers_inscrits = 0;


     printf("\tDébut du jeu\n");

     
     /* Ecriture du pid de aire.*/

     /*if((fd_vers = open(fich_vers, O_RDWR, 0666)) == -1){
         
         fprintf("%s : Pb d'ouverture du fichier des vers : %s\n", Nom_Prog, fich_vers);
         exit(-1);
     }*/

     if((noerr = vers_fichier_aire_ecrire(fich_vers, getpid()))== -1){

         fprintf(stderr, "%s : erreur dans vers_fichier_aire_ecrire\n", Nom_Prog);
         exit(noerr);
     }

     /*Ouverture du fichier terrain et Récupération des dimensions du terrain. Normalement, pas besoin de verrou puisqu'aire est le seul processus à écrire dans ce fichier*/

     if( (fd_terrain =  open(fich_terrain, O_RDWR, 0666)) == -1){
         
         fprintf("%s : pb ouverture du fichier terrain : %s\n", Nom_Prog, fich_terrain);
         exit(-1);
     }

     if((noerr = terrain_dim_lire(fd_terrain, &nb_lig, &nb_col)) ==-1){

         fprintf(stderr ,"%s : erreur %d dans terrain_dim_lire\n", Nom_Prog, noerr);
         exit(noerr);
     }

     /*On attend que le nombre de vers inscrits dans le fichier de vers soit egal au nbre de vers déclaré en argument*/
     /*On redirige le signal SIGUSR1 afin que le dernier ver a s'inscrire dans le fichier de vers previenne le processus aire que tous les vers sont inscrits, et que la partie peut demarrer.*/
     struct sigaction s_action;
     s_action.sa_handler = sig_handler_pret;
     sigemptyset(&s_action.sa_mask);
     sigaction(SIGUSR1, &s_action, NULL);
     
     /*On attend que tous les vers se soient inscrits*/
     while(e_nbre_vers_inscrits != nb_vers){

         pause();
     }

     sleep(TEMPS_COURT);

     /*On charge la liste des vers*/
     if((noerr = vers_liste_charger(fich_vers, &liste_vers, &nb_vers)) == -1){

             fprintf(stderr, "%s : erreur dans vers_liste_charger\n", Nom_Prog);
             exit(noerr);
     }
     else{
         
         printf("Liste des vers complète et chargée : \n");
         vers_liste_afficher(liste_vers, nb_vers);
     }

     /*On masque les signaux des vers lors de l'execution du handler*/
     for(v = 0; v < nb_vers; v++){

         sigaddset(&s_action.sa_mask, liste_vers[v].sig);
     }
     
     /*On redirige le signal vers le handler de jeu*/
     s_action.sa_handler =sig_handler_jeu;

     /*On initialise tous les vers à leur position de départ*/
     for(v = 0; v < nb_vers; v ++){

         if((noerr =jeu_ver_initialiser(fd_terrain, nb_lig, nb_col, &liste_vers[v])) ==-1){
             
             printf("\nImpossible de trouver une place pour le ver %c\n", liste_vers[v].marque);
         }
     }

     /*On envoie a tous les vers le signal de debut du jeu qui correspond a SIGUSR1*/
     for(v = 0; v < nb_vers; v++){

         kill(liste_vers[v].pid, SIGUSR1);
     }

     /*On attend qu'il n'y ai plus de ver actif dans la liste*/
     while(vers_liste_actifs(liste_vers, nb_vers)){

         pause();
     }

     printf("\n\nLe ver %c a gagné la partie\n\n", liste_vers[dernier].marque);

     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}

