#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>



/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     int fd_terrain ;
     char fich_terrain[128] ;
     char mess[256];
     struct flock verrou;
     struct stat buff;
     time_t dernier, actuel;
     char nomprog[256] ;
     int no_err = 0;


     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
         

     stat(fich_terrain, &buff);
     dernier = buff.st_mtime;
     actuel = dernier;
     int e_compte_tours =0;

     /*initialisation du verrou*/
     verrou.l_type = F_RDLCK;
     verrou.l_start = SEEK_SET;
     verrou.l_whence = 0;
     verrou.l_len = SEEK_END;
     
     if( ( fd_terrain = open( fich_terrain , O_RDONLY , 0644 )) == -1 ) {
         
         fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_terrain);
         exit(-1);
     }
     //printf(" Terrain initialise: \n");

     while(1){
         
         stat(fich_terrain, &buff);
         actuel = buff.st_mtime;
         printf("Test d'entree dans la boucle d'affichage,tour : %d\n", e_compte_tours++);

         while(actuel == dernier){
            stat(fich_terrain, &buff);
            actuel = buff.st_mtime;
         }


             dernier = actuel;
             verrou.l_type = F_RDLCK;
             fcntl(fd_terrain, F_SETLKW, verrou);
             printf("\n%s : --- Afffichage du terrain ---\n", nomprog);
             
             if( (no_err = terrain_afficher(fd_terrain) )){
                 
                 fprintf( stderr, "%s : erreur %d dans terrain_afficher\n",nomprog , no_err );
                 exit(no_err) ;
             }
             verrou.l_type = F_UNLCK;
             fcntl(fd_terrain, F_SETLKW, verrou);
             
         //}

         //sleep(1);
     }

     printf("\n%s : --- Arret de l'affichage du terrain ---\n", nomprog );
     close(fd_terrain);


     exit(0);
}
