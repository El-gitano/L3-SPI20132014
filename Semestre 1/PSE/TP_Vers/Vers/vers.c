/*
 * Gestion de la liste des vers 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>



/* 
 * Transformation d'un numero de signal en numero de ver 
 */

extern  
int
vers_sig2ind( const int signal ,
	      ver_t * const tab_vers,
	      const int nb_vers )
{
     booleen_t trouve = FAUX ;
     int i = 0 ;

     /*--------------------*/

     while( (i<nb_vers) && (!trouve) )
     {
	  if( tab_vers[i].sig == signal ) 
	       trouve = VRAI ;
	  else
	       i++ ;
     }

     if( trouve ) 
	  return(i) ;
     else
	  return(-1) ;
}


/* 
 * Affichage d'un ver
 */

extern
void
vers_afficher( FILE * const stream,
	       const ver_t ver )
{

     fprintf( stream , "{ tete=[%d,%d](%lld) , marque=%c , pid=%d , sig=%d , ",
	      ver.tete.y, ver.tete.x, (long long)ver.tete.pos,
	      ver.marque, ver.pid , ver.sig );
     if( ver.actif )
	  fprintf( stream , "ACTIF }");
     else
	  fprintf( stream , "MORT }");

}

/*
 * Affichage d'une liste de vers 
 */

extern  
void
vers_liste_afficher( ver_t * const tab_vers,
		     const int nb_vers )
{
     int i = 0 ;

     /*--------------------*/

     fprintf( stdout , "\n----- Debut liste vers -----\n");

     for(i=0 ; i<nb_vers ; i++)
     {
	  vers_afficher( stdout , tab_vers[i] );
	  fprintf( stdout , "\n");
     }
     fprintf( stdout , "----- Fin liste vers -----\n\n");
}

/*
 *  Teste si il n'y au plus un ver dans le terrain
 */ 

extern
booleen_t
vers_liste_dernier( ver_t * const tab_vers,	/* liste des vers */
		    const int nb_vers ,	/* nombre de vers dans la liste */
		    int * dernier_ver )	/* indice du dernier ver */
{
     int i = 0 ;
     int nb_actifs = 0 ;

     /*----------*/

     for( i=0 ; i<nb_vers ; i++ )
     {
	  if( tab_vers[i].actif )
	  {
	       (*dernier_ver) = i ;
	       nb_actifs++ ;
	  }
     }
     
     if( nb_actifs == 1 )
	  return(VRAI) ;
     else
     {
	  (*dernier_ver) = -1 ;
	  return(FAUX) ;
     }
}

/*
 *  Teste si il n'y a plus de vers actifs
 *  Renvoie VRAI si il y a au moins un vers actif
 *          FAUX sinon
 */ 

extern
booleen_t
vers_liste_actifs( ver_t * const tab_vers,	/* liste des vers */
		   const int nb_vers )	/* nombre de vers dans la liste */
{
     int i = 0 ;
     booleen_t actifs = FAUX ;

     /*----------*/

     while( (i<nb_vers) && (!actifs) )
     {
	  if( tab_vers[i].actif )
	       actifs = VRAI ;
	  i++;
     }
     
     return(actifs) ;
}

/* 
 * Chargement d'une liste de vers a partir d'un fichier de sauvegarde
 * Format du fichier : 
 * <nombre de vers> 
 * <signal> <marque> <pid>                      
 */

extern
int
vers_liste_charger( char * const fichier_vers,	/* Fichier de sauvegarde des vers */
		    ver_t ** liste_vers,	/* liste des vers */
		    int * nb_vers )	/* Nombre de vers dans la liste */
{
     static booleen_t first = VRAI ;
     int fd_vers;
     ver_t ver ;
     char mess[128] ;
     ssize_t  nb_lus ;
     int v ;

     /*----------*/

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fichier_vers , O_RDONLY, 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fichier_vers);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Lecture du nombre de vers 
      */
     
     if( read( fd_vers , nb_vers , sizeof(int)) == -1 )
     {
	  perror( "vers_liste_charger : Pb read sur lecture nombre de vers\n");
	  return(ERREUR) ;
     }

#ifdef _DEBUG_ 
     printf("vers_liste_charger --> chargement des %d vers de %s\n", 
	    (*nb_vers), fichier_vers );
#endif

     /*
      * Saut du pid du processus aire 
      */
     
     if( lseek( fd_vers , sizeof(pid_t) , SEEK_CUR) == -1 )
     {
	  perror( "vers_liste_charger : Pb lseek sur saut du pid aire\n");
	  return(ERREUR) ;
     }
     
     /* 
      * Creation liste des vers
      */

     for( v=0 ; v < (*nb_vers) ; v++ )
     {
	  /* Lecture d'un ver */
	  if( (nb_lus = read(fd_vers , &ver , sizeof(ver_t))) != sizeof(ver_t) )
	  {
	       sprintf( mess, "vers_liste_charger : Pb dans la lecture d'un ver, %zu octets lus au lieu de %zu\n",
			nb_lus , sizeof(ver_t) );
	       perror(mess) ;
	       fprintf( stderr, " Structure de ver lue = ");
	       vers_afficher( stderr , ver );
	       fprintf( stderr , "\n" );
	       return(ERREUR);
	  }

	  /* Chargement du ver dans la liste */
	  if( first )
	  {
	       (*liste_vers)= (ver_t *)malloc(sizeof(ver_t));
	       first = FAUX ;
	  }
	  else
	  {
	       (*liste_vers) = (ver_t *)realloc((*liste_vers),sizeof(ver_t)*((*nb_vers)+1));
	  }

	  (*liste_vers)[v] = ver ;
     }
	  

     /*
      * Fermeture fichier des vers 
      */
     close(fd_vers) ;

#ifdef _DEBUG_ 
     printf("vers_liste_charger --> affichage des %d vers de la liste %s\n",
	    (*nb_vers), fichier_vers );
     vers_liste_afficher( (*liste_vers) , (*nb_vers) );
#endif
     return(CORRECT) ;
}

/* 
 * Ajout d'un ver dans un fichier de vers 
 */

extern 
int
vers_fichier_ajouter( char * const fichier_vers,	/* Reference fichier vers */
		      const ver_t ver )			/* Ver a ajouter */
{
     int fd_vers;
     char mess[128] ;
     ssize_t  nb_ecrits ;
     int nb_vers ;

     /*----------*/

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fichier_vers , O_RDWR , 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fichier_vers);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Mise a jour du nombre de vers 
      */
     
     if( read( fd_vers , &nb_vers , sizeof(int)) == -1 )
     {
	  perror( "vers_fichier_ajouter : Pb read sur lecture nombre de vers\n");
	  return(ERREUR) ;
     }

#ifdef _DEBUG_ 
     printf("vers_fichier_ajouter --> nombre de vers dans %s avant ajout = %d\n", 
	    fichier_vers , nb_vers );
#endif

     nb_vers++ ;

     if( lseek( fd_vers , 0 ,SEEK_SET) == -1 )
     {
	  perror( "vers_fichier_ajouter : Pb lseek sur deplacement au debut fichier vers\n");
	  return(ERREUR) ;
     }

     if( write( fd_vers , &nb_vers , sizeof(int)) == -1 )
     {
	  perror( "vers_fichier_ajouter : Pb write sur ecriture nombre de vers\n");
	  return(ERREUR) ;
     }

     /* 
      * Ajout d'un ver en fin de fichier 
      */

       if( lseek( fd_vers , 0 , SEEK_END ) == -1 ) 
       { 
  	  perror( "vers_fichier_ajouter : Pb lseek sur deplacement en fin de fichier vers\n"); 
  	  return(ERREUR) ; 
       } 


     if( (nb_ecrits =write( fd_vers , &ver , sizeof(ver_t)) != sizeof(ver_t)) )
     {
	  sprintf( mess, "vers_fichier_ajouter : Pb dans la lecture d'un ver, %zu octets ecrits au lieu de %zu\n",
			nb_ecrits , sizeof(ver_t) );
	  perror(mess) ;
	  fprintf( stderr, " Structure de ver a ecrire = ");
	  vers_afficher( stderr , ver );
	  fprintf( stderr , "\n" );
	  return(ERREUR);
     }

#ifdef _DEBUG_
       printf( " Structure de ver ecrit = ");
       vers_afficher( stdout , ver );
       printf( "\n" );
#endif	  

     /*
      * Fermeture fichier des vers 
      */

     close(fd_vers) ;

#ifdef _DEBUG_ 
     printf(  "vers_fichier_ajouter --> Ajout effectue dans la liste %s du ver\n ",
	    fichier_vers );
     vers_afficher( stdout , ver );
     printf("\nFichier mis a jour:\n");
     vers_fichier_afficher(fichier_vers);
#endif

     return(CORRECT) ;
}

/* 
 * Ecriture du pid de l'aire dans le fichier des vers
 */

extern 
int
vers_fichier_aire_ecrire( char * const fichier_vers,	/* Reference fichier vers */
			   const pid_t pid_aire )	/* Pid a ecrire */
{
     int fd_vers;
     char mess[128] ;

     /*----------*/

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fichier_vers , O_RDWR , 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fichier_vers);
	  perror(mess);
	  return(ERREUR);
     }

     
     /* 
      * Saut du nombre de vers 
      */

     if( lseek( fd_vers , sizeof(int)  ,SEEK_SET) == -1 )
     {
	  perror( "vers_fichier_ajouter : Pb lseek sur saut du nb de vers\n");
	  return(ERREUR) ;
     }

     /* 
      * Ecriture du pid du processus aire
      */

     if( write( fd_vers , &pid_aire , sizeof(pid_t)) == -1 )
     {
	  perror( "vers_fichier_ajouter : Pb write sur ecriture pid aire\n");
	  return(ERREUR) ;
     }

     /*
      * Fermeture fichier des vers 
      */

     close(fd_vers) ;

#ifdef _DEBUG_ 
     printf(  "vers_aire_ecrire --> Ecriture du pid aire %d effectuee dans la liste des vers %s\n",
	    pid_aire , fichier_vers );
#endif

     return(CORRECT) ;
}


/* 
 * Lecture du pid de l'aire dans le fichier des vers
 */

extern 
int
vers_fichier_aire_lire( char * const fichier_vers,	/* Reference fichier vers */
			pid_t * pid_aire )	/* Pid a lire */
{
     int fd_vers;
     char mess[128] ;

     /*----------*/

     /* 
      * Initialisation du resultat 
      */
     (*pid_aire) = 0 ;

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fichier_vers , O_RDONLY , 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fichier_vers);
	  perror(mess);
	  return(ERREUR);
     }

     
     /* 
      * Saut du nombre de vers 
      */

     if( lseek( fd_vers , sizeof(int) ,SEEK_SET) == -1 ) 
     { 
	  perror( "vers_fichier_ajouter : Pb lseek sur saut du nb de vers\n"); 
	  return(ERREUR) ; 
     } 

     /* 
      * Lecture du pid du processus aire
      */

     if( read( fd_vers , pid_aire , sizeof(pid_t)) == -1  )
     {
	  perror( "vers_aire_lire : Pb read sur lecture pid aire\n");
	  return(ERREUR) ;
     }

     /*
      * Fermeture fichier des vers 
      */

     close(fd_vers) ;

#ifdef _DEBUG_ 
     printf(  "vers_aire_lire --> Lecture du pid aire %d effectuee dans la liste des vers %s\n",
	    (*pid_aire) , fichier_vers );
#endif

     return(CORRECT) ;
}


/* 
 * Affichage d'un fichier de vers                      
 */

extern
int
vers_fichier_afficher( char * const fichier_vers )	
{
     int fd_vers;
     int nb_vers ;
     pid_t pid_aire ;

     ver_t ver ;
     char mess[128] ;
     ssize_t  nb_lus ;
     int v ;

     /*----------*/

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fichier_vers , O_RDONLY, 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fichier_vers);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Lecture du nombre de vers 
      */
     
     if( read( fd_vers , &nb_vers , sizeof(int)) == -1 )
     {
	  perror( "vers_fichier_afficher : Pb read sur lecture nombre de vers\n");
	  return(ERREUR) ;
     }

     /*
      * Lecture du pid du processus aire 
      */
     
     if( read( fd_vers , &pid_aire , sizeof(pid_t)) == -1 )
     {
	  perror( "vers_fichier_afficher : Pb read sur lecture nombre de vers\n");
	  return(ERREUR) ;
     }
     
     printf( "NB VERS = %d , PID AIRE = %d\n",
	     nb_vers , pid_aire );
     /* 
      * Affichage corps de la liste 
      */

     for( v=0 ; v < nb_vers ; v++ )
     {
	  /* Lecture d'un ver */
	  if( (nb_lus = read(fd_vers , &ver  , sizeof(ver_t))) != sizeof(ver_t) )
	  {
	       sprintf( mess, "vers_fichier_afficher : Pb dans la lecture d'un ver, %zu octets lus au lieu de %zu\n",
			nb_lus , sizeof(ver_t) );
	       perror(mess) ;
	       fprintf( stderr, " Structure de ver lue = ");
	       vers_afficher( stderr , ver );
	       fprintf( stderr , "\n" );
	       return(ERREUR);
	  }

	  vers_afficher( stdout , ver );
	  fprintf( stdout , "\n" );
     }
	  
     /*
      * Fermeture fichier des vers 
      */
     close(fd_vers) ;

     return(CORRECT) ;
}


/*
 * Initialisation d'un fichier de vers 
 */

extern 
int
vers_fichier_initialiser( char * const fich_vers )	/* Reference du fichier des vers */
{
     int fd_vers ;
     char mess[128] ;
     int nb_vers = 0 ;
     pid_t pid_aire = 0 ;

     /*--------------------*/

     /* 
      * Ouverture fichier de sauvegarde des vers
      */

     if( ( fd_vers = open( fich_vers , O_WRONLY | O_CREAT | O_TRUNC , 0666)) == -1 )
     {
	  sprintf( mess, "vers_fichier_initialiser : Pb open sur %s", fich_vers);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Ecriture de la ligne d'entete
      */

     if( write( fd_vers , &nb_vers , sizeof(int)) == -1 )
     {
	  perror( "Pb write sur ecriture nb_vers");
	  exit(-1);
     }

     if( write( fd_vers , &pid_aire , sizeof(pid_t)) == -1 )
     {
	  perror( "Pb write sur ecriture pid aire");
	  exit(-1) ;
     }

     /*
      * Fermeture fichier des vers 
      */

     close(fd_vers) ;
     
     return(CORRECT);

}
