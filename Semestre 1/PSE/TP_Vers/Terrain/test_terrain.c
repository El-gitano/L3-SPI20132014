#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>


int
main( int nb_arg , char * tab_arg[] )
{
     int fd_terrain ;
     int no_err = 0 ;
     char fich_terrain[128] ;
     coord_t * liste_voisins = (coord_t *)NULL ;
     int nb_voisins = 0 ;
     int ind_libre = 0 ;
     coord_t tete ;
     case_t marque = TERRAIN_CASE_LIBRE ;
     char nomprog[128] ;
     int v ;
     
     int nb_lig = 10 ;
     int nb_col = 15 ;

     /*----------*/

     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <nom fichier terrain> <marque>\n",
		   tab_arg[0] );
	  exit(-1) ;
     }

     if( strlen(tab_arg[2]) !=1 ) 
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   tab_arg[0] , tab_arg[2] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] ) ;
     marque = tab_arg[2][0] ;

     /*
      * Creation terrain 
      */

     if( (no_err = terrain_initialiser( fich_terrain,nb_lig,nb_col)) )
     {
	  fprintf( stderr, "%s : erreur %d dans terrain_initialiser\n",
		   nomprog , no_err );
	  exit(no_err) ;
     }

     /* 
      * Ouverture fichier aire de jeu 
      */

     if( ( fd_terrain = open( fich_terrain , O_RDWR , 0644 )) == -1 )
     {
	  fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_terrain);
	  exit(-1);
     }

     printf(" Terrain initialise: \n");

     if( (no_err = terrain_afficher(fd_terrain) )) 
     {
	  fprintf( stderr, "%s : erreur %d dans terrain_afficher\n",
		   nomprog , no_err );
	  exit(no_err) ;
     }


     tete.x = 5 ;
     tete.y = 6 ;
     tete.pos = TERRAIN_TAILLE_ENTETE + ( tete.y*TERRAIN_TAILLE_CASE*nb_col ) + (tete.x*TERRAIN_TAILLE_CASE) ;

     printf(" Ecriture de la case[%d,%d]\n", tete.y, tete.x );

     if( (no_err = terrain_marque_ecrire( fd_terrain,
					  tete,
					  marque ) ) )
     {
	  fprintf( stderr, "%s : erreur %d dans terrain_marque_ecrire\n",
		   nomprog , no_err );
	  exit(no_err) ;
     }

     if( (no_err = terrain_afficher(fd_terrain) )) 
     {
	  fprintf( stderr, "%s : erreur %d dans terrain_afficher\n",
		   nomprog , no_err );
	  exit(no_err) ;
     }
     for( v=0 ; v<9; v++)
     {
	  printf(" Recherche des voisins de la case[%d,%d]\n",
		 tete.y, tete.x );
   
	  if( (no_err = terrain_voisins_rechercher( fd_terrain,
						    tete,
						    &liste_voisins,
						    &nb_voisins)) )
	  {
	       fprintf( stderr, "%s : erreur %d dans terrain_voisins_rechercher\n",
			nomprog , no_err );
	       exit(no_err) ;
	  }

	  printf(" Affichage des voisins de la case[%d,%d]\n",
		 tete.y, tete.x );

	  terrain_voisins_afficher( fd_terrain,
				    liste_voisins,
				    nb_voisins) ;
     
	  printf(" Recherche d'une case libre dans la liste des voisins\n");


	  if( (no_err = terrain_case_libre_rechercher( fd_terrain,
						       liste_voisins,
						       nb_voisins,		
						       &ind_libre )) )     
	  {
	       fprintf( stderr, "%s : erreur %d dans terrain_case_libre_rechercher\n",
			nomprog , no_err );
	       exit(no_err) ;
	  }
	
	  if( ind_libre == -1 )
	  {
	       printf( "Pas de case voisine libre\n");
	  }
	  else
	  {
	       printf(" Ecriture dans la case libre choisie ==> %d\n" , ind_libre );

	       if( (no_err = terrain_marque_ecrire( fd_terrain,
						    liste_voisins[ind_libre],
						    marque ) ) )
	       {
		    fprintf( stderr, "%s : erreur %d dans terrain_marque_ecrire\n",
			     nomprog , no_err );
		    exit(no_err) ;
	       }
	  }
	  

	  if( (no_err = terrain_afficher(fd_terrain) )) 
	  {
	       fprintf( stderr, "%s : erreur %d dans terrain_afficher\n",
			nomprog , no_err );
	       exit(no_err) ;
	  }	  
     }

     free(liste_voisins); 
     close(fd_terrain); 

     exit(0);

}
