#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <vers.h>


int
main( int nb_arg , char * tab_arg[] )
{
     ver_t ver1 ;
     char fich_vers[128];
     int i , n ; 
     int nb_vers ;
     ver_t * liste_vers = (ver_t *) NULL ; /* ATTENTION a bien initialiser la liste des vers */
     int dernier ;
     pid_t pid_aire ;

     /*----------*/

     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <fichier vers> <n>\n",
		   tab_arg[0] );
	  exit(-1) ;
     }

     strcpy( fich_vers , tab_arg[1]) ;
     sscanf( tab_arg[2] , "%d" , &n ) ;

     ver1.tete.x = n+1 ;
     ver1.tete.y = n+2 ;
     ver1.tete.pos = n+3 ;
     ver1.marque = 'A'+n ;
     ver1.pid = n+100 ;
     ver1.sig = n+10 ;
     ver1.actif = VRAI ;

     /* Initialisation fichier */
     vers_fichier_initialiser( fich_vers ) ;

     /* Test ecriture pid processus aire dans le fichier des vers */
     vers_fichier_aire_ecrire( fich_vers, getpid()) ;

     /* Test ajout de vers dans le fichier */
     for( i=0 ; i<3 ; i++ )
     {
	  ver1.sig++  ;
	  ver1.marque++  ;
	  vers_fichier_ajouter( fich_vers, ver1 ) ;
     }

     /* Test affichage fichier des vers */
     vers_fichier_afficher(fich_vers);

     /* Test lecture du pid du processus aire */
     vers_fichier_aire_lire(fich_vers, &pid_aire);
     printf(" Le pid du processus aire dans le fichier des vers est %d\n",
	    pid_aire ) ;
     
     /* Test chargement fichier dans liste de vers */
     vers_liste_charger( fich_vers, &liste_vers, &nb_vers) ;

     /* Test affichage d'une liste de vers */
     vers_liste_afficher( liste_vers, nb_vers) ;

     /* Test conversion signal --> num de vers */
     printf( "Le signal numero %d correspond au ver numero %d dans la liste des vers\n",
	     10+n+1 , vers_sig2ind( 10+n+1 , liste_vers , nb_vers ) ) ;

     if( vers_liste_actifs( liste_vers , nb_vers ) )
     {
	  printf(" Il y a au moins un ver actif dans la liste\n");
	  if( vers_liste_dernier(liste_vers, nb_vers, &dernier) )
	  {
	       printf(" Il n'y a qu'un ver actif dans la liste et son indice dans la liste est %d\n" ,
		      dernier );

	  }
     }



     exit(0);
}
