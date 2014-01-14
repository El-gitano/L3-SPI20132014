#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>

int
main( int nb_arg , char * tab_arg[] )
{

     /* Parametres */
     char fich_terrain[128] ;
     case_t marque = TERRAIN_CASE_LIBRE ;
     char nomprog[128] ;

     /* variables generales */
     char mess[256];
     booleen_t arret = FAUX ;
     int no_err = 0;

     /* variables terrain */
     int fd_terrain ;
     coord_t * liste_voisins = (coord_t *)NULL ;
     int nb_voisins = 0 ;
     int ind_libre = 0 ;
     int nb_lig ;
     int nb_col ;

     /* variables ver */
     ver_t ver ;


     /*----------*/

     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <marque>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     if( strlen(tab_arg[2]) !=1 ) 
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   tab_arg[0] , tab_arg[2] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     marque = tab_arg[2][0] ;

     printf( "\n\n%s : ----- Debut du ver %c (%d) -----\n\n ", 
	     nomprog , marque , getpid() );


     ver.marque = marque;
     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());


     /*Ouverture du fichier terrain*/

     if( ( fd_terrain = open( fich_terrain , O_RDWR , 0644 )) == -1 ) {
         
         fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_terrain);
         exit(-1);
     }
     
     /*Création du verrou*/
     struct flock serrure;
     serrure.l_type = F_WRLCK;
     serrure.l_whence = 0;
     serrure.l_start = SEEK_SET;
     serrure.l_len = SEEK_END;

     /*Pose du verrou*/
     fcntl(fd_terrain, F_SETLKW, serrure);


     /*Recuperation des dimensions du terrain*/
     if((no_err = terrain_dim_lire(fd_terrain, &nb_lig, &nb_col))){
         fprintf(stderr, "%s : erreur %d dans terrain_dim_lire\n", nomprog, no_err);
         exit(no_err);
     }
     printf("Dimensions du terrain récupérées\n");
     if((no_err = terrain_initialiser(fich_terrain, nb_lig, nb_col))){
         fprintf("\n", nomprog, no_err);
         exit(no_err);
     }
     
     /*Levée du verrou*/
     serrure.l_type = F_UNLCK;
     fcntl(fd_terrain, F_SETLKW, serrure);


     /*Initialisation des coordonées de départ du ver sur une case vide*/
        
    /*Pose du verrou*/
    serrure.l_type = F_WRLCK;
    fcntl(fd_terrain, F_SETLKW, serrure);
    
    jeu_ver_initialiser(fd_terrain, nb_lig, nb_col, &ver);

    /*Levée du verrou*/
    serrure.l_type = F_UNLCK;
    fcntl(fd_terrain, F_SETLKW, serrure);

     do {
 
        /*Pose du verrou*/
        serrure.l_type = F_WRLCK;
        fcntl(fd_terrain, F_SETLKW, serrure);

        /*Recherche d'une case libre*/
        if((no_err = terrain_voisins_rechercher(fd_terrain,ver.tete, &liste_voisins, &nb_voisins))){
            fprintf(stderr, "%s : erreur %d dans terrain_voisin_rechercher\n", nomprog, no_err);
            exit(no_err);
        }
        /*Choix aléatoire d'une case libre dans la liste des voisins*/
        if((no_err = terrain_case_libre_rechercher(fd_terrain, liste_voisins, nb_voisins, &ind_libre))){
                fprintf(stderr, "%s : erreur %d dans terrain_case_libre_rechercher\n", nomprog, no_err);
                exit(no_err);
        }

        ver.actif = FAUX;
  

        if(ind_libre != -1){

            if((no_err = terrain_marque_ecrire(fd_terrain, liste_voisins[ind_libre], ver.marque))){
                fprintf(stderr, "%s : erreur %d dans terrain_marque_ecrire\n", nomprog, no_err);
                exit(no_err);
            }

            /*Mise à jour de la tete du ver*/
            printf("Tete du ver %c mise à jour\n", ver.marque); 
            ver.tete.pos = liste_voisins[ind_libre].pos;
            ver.tete.x = liste_voisins[ind_libre].x;
            ver.tete.y = liste_voisins[ind_libre].y;

            ver.actif = VRAI;

            //terrain_afficher(fd_terrain);

            /*Délai d'attente afin de laisser jouer d'autres vers*/
            sleep(random() % TEMPS_MOYEN);

        }
        else {
            printf("Mort du ver %c !\n",ver.marque);
        }

        /*Levée du verrou*/
        serrure.l_type = F_UNLCK;
        fcntl(fd_terrain, F_SETLKW, serrure);

     }while(ver.actif == VRAI);


     printf( "\n\n%s : ----- Fin du ver %c (%d) -----\n\n ", 
	     nomprog , marque , getpid() );

     exit(0);
     return EXIT_SUCCESS;
}
