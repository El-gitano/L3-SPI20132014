#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>

/* 
 * Affichage du terrain
 */

extern 
int
terrain_afficher( const int fd )
{
     
     int nb_lig = 0 ; 
     int nb_col = 0 ; 
     char cellule = TERRAIN_CASE_LIBRE ;
     int l,c ; 
     char mess[256];

     /*----------*/

     /* 
      * Mise de la position courante au debut du fichier
      */

     if( lseek(fd, (off_t)0, SEEK_SET) == -1 )
     {
	  perror("terrain_afficher : Pb lseek debut fichier \n");
	  return(ERREUR) ;
     }

     /* 
      * Lecture des dimensions du terrain 
      */
     
     if( read( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  perror("terrain_afficher : Pb read sur lecture nb lignes");
	  return(ERREUR) ;
     }

     if( read( fd , &nb_col , sizeof(int)) == -1 )
     {
	  perror( "terrain_afficher : Pb read sur lecture nb colonnes");
	  return(ERREUR) ;
     }

#ifdef _DEBUG_ 
     printf("terrain_afficher --> affichage aire de jeu [%d,%d]\n", 
	    nb_lig , nb_col );
#endif

     /* 
      * Affichage de l'aire de jeu
      */

     /* Affichage 1ere ligne */
     for( c=0 ; c<nb_col ; c++ ) fprintf( stdout , ".---" ); fprintf(stdout , ".\n");

     /* Affichage corps */
     for( l=0 ; l<nb_lig; l++ )
     {
	  for( c=0 ; c<nb_col ; c++ )
	  {
	       if( read( fd , &cellule, sizeof(char)) == -1 )
	       {
		    sprintf( mess , "terrain_afficher : erreur sur lecture aire[%i,%i]\n",l,c);
		    perror(mess);
		    return(ERREUR) ;
	       }
	       fprintf( stdout , "| %c " , cellule );
	  }
	  
	  fprintf(stdout , "|\n");
	  if( l != nb_lig-1 )
	  {
	       for( c=0 ; c<nb_col ; c++ ) fprintf( stdout , "|---" ); fprintf(stdout , "|\n");
	  }
	  
     }

     /* Affichage derniere ligne */
     fprintf( stdout , "`---" ) ;for( c=1 ; c<nb_col ; c++ ) fprintf( stdout , "----" ); fprintf(stdout , "'\n");

     return(CORRECT);
}


/* 
 * Initialisation de l'aire de jeu
 */

extern 
int 
terrain_initialiser( const char * fich_terrain , int nb_lig , int nb_col )
{
     int fd ;
     int l,c ;
     case_t tcl = TERRAIN_CASE_LIBRE ;
     char mess[256] ;

     /*----------*/

#ifdef _DEBUG_ 
     printf("terrain_init --> debut initialisation aire de jeu %s[%d,%d]\n", 
	    fich_terrain , nb_lig , nb_col );
#endif

     /* 
      * Ouverture fichier aire de jeu 
      */
     if( ( fd = open( fich_terrain , O_WRONLY | O_CREAT , 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fich_terrain);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Ecriture des dimensions 
      */
     
     if( write( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  sprintf( mess , "terrain_init : erreur sur ecriture nb lignes=%i\n", nb_lig );
	  perror(mess);
	  return(ERREUR) ;
     }

     if( write( fd , &nb_col , sizeof(int)) == -1 )
     {
	  sprintf( mess , "terrain_init : erreur sur ecriture nb colonnes=%i\n", nb_col);
	  perror(mess);
	  return(ERREUR) ;
     }

     /* 
      * Ecriture de l'aire de jeu vide
      */

     for( l=0 ; l<nb_lig ; l++ )
     {
	  for( c=0 ; c<nb_col ; c++ )
	  {
	       if( write( fd , &tcl , TERRAIN_TAILLE_CASE) == -1 )
	       {
		    sprintf( mess , "terrain_init : erreur sur ecriture %s[%i,%i]\n",fich_terrain, l,c);
		    perror(mess);
		    return(ERREUR) ;
	       }
	  }
     }

     /*
      * Fermeture fichier aire de jeu 
      */
     close(fd);

#ifdef _DEBUG_ 
     printf("terrain_init --> fin initialisation aire de jeu %s\n", fich_terrain);
#endif

     return(CORRECT);
}


/*
 * Recherche des cases voisines d'une case[y,x] dans le terrain 
 */

extern
int 
terrain_voisins_rechercher( const int fd,		/* descripteur fichier terrain */
			    const coord_t coord,	/* coordonnees case */
			    coord_t ** liste_voisins, /* coordonnees des cases voisines */
			    int * nb_voisins )		/* nb de voisins */
{
     int nb_lig , nb_col , l , c ;
     size_t taille_entete = TERRAIN_TAILLE_ENTETE ;
     size_t taille_case =  TERRAIN_TAILLE_CASE ;
     size_t taille_ligne ;
     static booleen_t first = VRAI ;

     /*----------*/

     /* 
      * Mise de la position courante au debut du fichier
      */

     lseek(fd, (off_t)0, SEEK_SET);

     /* 
      * Lecture des dimensions du terrain 
      */
     
     if( read( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  perror( "terrain_voisins_rechercher : Pb read sur lecture nb lignes\n");
	  return(ERREUR) ;
     }

     if( read( fd , &nb_col , sizeof(int)) == -1 )
     {
	  perror("terrain_voisins_rechercher : Pb read sur lecture nb colonnes\n");
	  return(ERREUR) ;
     }

#ifdef _DEBUG_ 
     printf("terrain_voisins_rechercher --> recherche des voisins de la case[%d,%d](%lld) dans terrain[%d,%d]\n", 
	    coord.y , coord.x , (long long)coord.pos , nb_lig , nb_col );
#endif

     taille_ligne = (size_t)(nb_col*taille_case) ;

     /* 
      * Creation liste des coordonnees des voisins 
      */

     (*nb_voisins) = 0 ;

     l = ( coord.y-1>0 ? coord.y-1 : 0 ) ;
     while( (l<nb_lig) && (l<coord.y+2)  )
     {
	  c = ( coord.x-1>0 ? coord.x-1 : 0 ) ;
	  while( (c<nb_col) && (c<coord.x+2) )
	  {
	       if( (l != coord.y) || (c != coord.x) )
	       {
		    if( first )
		    {
			 (*liste_voisins)= (coord_t *)malloc(sizeof(coord_t));
			 first = FAUX ;
		    }
		    else
		    {
			 (*liste_voisins) = (coord_t *)realloc((*liste_voisins),sizeof(coord_t)*((*nb_voisins)+1));
		    }

		    (*liste_voisins)[(*nb_voisins)].x = c ;
		    (*liste_voisins)[(*nb_voisins)].y = l ;
		    (*liste_voisins)[(*nb_voisins)].pos = (off_t)(taille_entete + (l*taille_ligne) + (c*taille_case));

		    (*nb_voisins)++ ;
	       }

	       c++ ;
	  }
	  l++ ;
     }
	  
     return(CORRECT) ;
}

/* 
 * Choix aleatoire d'une case libre parmi une liste de voisins
 * Resultat dans <ind_case_libre> . Si il n'existe pas de cases
 * libres alors <ind_case_libre> est egal a -1.
 */

extern 
int
terrain_case_libre_rechercher( const int fd ,
			       coord_t * const liste_voisins ,
			       const int nb_voisins,
			       int * ind_case_libre )
{
     case_t case_voisin ;
     int ind_voisin ;
     int debut ;
     booleen_t trouve ;
     char mess[256] ;

     static booleen_t first = VRAI ;

     /*----------*/

     /*
      * Initialisation resultat 
      */

     (*ind_case_libre) = -1 ;

     /* 
      * Test liste vide 
      */

     if( nb_voisins == 0 )
	  return(CORRECT) ;

     /* 
      * Traitement liste au moins un voisin 
      */

     /* Initialisation de la fonction random */  
     if( first )
     {
	  srandom((unsigned int)time((time_t *)NULL)) ;
	  first = FAUX ;
     }

     /* Choix aleatoire de la 1ere case */
     ind_voisin = (int)(random() % nb_voisins) ;

#ifdef _DEBUG_ 
     printf("terrain_case_libre_rechercher --> case libre choisie = %d\n", 
	    ind_voisin );
#endif

     /* 
      * Renvoie la 1ere case si elle est libre 
      */
     if( lseek(fd,  liste_voisins[ind_voisin].pos, SEEK_SET) == -1 )
     {
	  sprintf( mess, "terrain_case_libre_rechercher : Pb lseek a la position %lld\n",
		   (long long)liste_voisins[ind_voisin].pos );
	  perror(mess);
	  return(ERREUR) ;
     }

     if( read( fd , &case_voisin , TERRAIN_TAILLE_CASE) == -1 )
     {
	  perror("terrain_case_libre_rechercher : Pb lecture 1ere case\n");
	  return(ERREUR) ;
     }

     if( case_voisin == TERRAIN_CASE_LIBRE )
     {
	  (*ind_case_libre) = ind_voisin ;
	  return(CORRECT);
     }

     /* 
      * Sinon parcours cyclique de la liste 
      */
	  
     debut = ind_voisin ;
     ind_voisin = (ind_voisin+1) % nb_voisins ;
     trouve = FAUX ;
     while( (ind_voisin != debut) && (! trouve) )
     {
	
	  if( lseek(fd, liste_voisins[ind_voisin].pos, SEEK_SET) == -1 )
	  {
	       sprintf( mess , "terrain_case_libre_rechercher : Pb lseek a la position %lld\n",
			(long long) liste_voisins[ind_voisin].pos );
	       perror(mess);
	       return(ERREUR) ;
	  }
	  if( read(fd, &case_voisin , TERRAIN_TAILLE_CASE) == -1 )
	  {
	       perror("terrain_case_libre_rechercher : Pb lecture 1ere case\n");
	       return(ERREUR) ;
	  }
	  
	  if( case_voisin == TERRAIN_CASE_LIBRE )
	  {
	       (*ind_case_libre) = ind_voisin ;
	       trouve = VRAI ;
	  }
	  else
	  {
	       ind_voisin=(ind_voisin+1)%nb_voisins ;
	  }
     }

     return(CORRECT);
}



 
/* 
 * Ecriture de <marque> a la position <position> dans <fd>
 */

extern
int 
terrain_marque_ecrire( const int fd,
		       const coord_t coord,
		       const case_t marque )
{
     case_t m = marque ;
     char mess[256] ;

     /*----------*/

#ifdef _DEBUG_ 
     printf("terrain_marque_ecrire --> ecriture %c a case[%d,%d](%lld)\n", 
	    marque , coord.y , coord.x , (long long)coord.pos );
#endif

     if( lseek( fd, coord.pos, SEEK_SET ) == -1 )
     {
	  sprintf( mess , "terrain_marque_ecrire : erreur dans deplacement a la position %lld dans le fichier terrain\n",
		   (long long)coord.pos );
	  perror(mess);
	  return(ERREUR) ;
     }

     write(fd, &m, TERRAIN_TAILLE_CASE) ;

     return(CORRECT) ;
}
		       


/* 
 * Affichage d'une liste de cases voisines
 */

static 
int 
terrain_rech_minmax_x( coord_t * const liste_voisins ,
		       const int nb_voisins ,
		       int * min,
		       int * max)
{
     int ind_voisin ;

     /*----------*/

     (*min)= 99999 ;
     (*max)= -1 ;

     for(ind_voisin=0 ; ind_voisin < nb_voisins ; ind_voisin++) 
     {
	  if( (*min) > liste_voisins[ind_voisin].x )
	       (*min) = liste_voisins[ind_voisin].x ;

	  if( (*max) < liste_voisins[ind_voisin].x )
	       (*max) = liste_voisins[ind_voisin].x ;
     }

     return(CORRECT);
}

static
int
terrain_voisins_marque_afficher( const int fd ,
				 coord_t * const liste_voisins ,
				 const int nb_voisins )
{
     case_t case_voisin ;
     int ind_voisin ;
     int l , c ;
     int min_col , max_col ; 

     /*----------*/

     /* 
      * Entete tableau 
      */

     terrain_rech_minmax_x( liste_voisins, nb_voisins,
			    &min_col , &max_col );
     printf("    ");
     for( c = min_col ; c <= max_col ; c++ )
	  printf("|%2d " , c );
     printf("|\n") ;

     printf("----");
     for( c = min_col ; c <= max_col ; c++ )
	  printf("|---");
     printf("|\n") ;


     /*
      * Corps tableau 
      */

     ind_voisin=0 ;
     while( ind_voisin < nb_voisins ) 
     {
	  /* Debut 1 ligne */

	  l = liste_voisins[ind_voisin].y ;
	  printf( " %2d " , l ) ;

	  /* Corps 1 ligne */

	  while( (ind_voisin < nb_voisins) &&
		 (l == liste_voisins[ind_voisin].y ) )
	  {
	       c = min_col ;

	       while( (ind_voisin < nb_voisins) &&
		      (l == liste_voisins[ind_voisin].y ) &&
		      ( c <= max_col ) )
	       {
	       
		    if( c == liste_voisins[ind_voisin].x ) 
		    {
			 /* Affichage 1 case */
			 
			 lseek(fd, liste_voisins[ind_voisin].pos, SEEK_SET);
			 read(fd, &case_voisin , TERRAIN_TAILLE_CASE );
			 
			 printf("| %c " , case_voisin );

			 ind_voisin++ ;
		    }
		    else
		    {
			 printf("|///");

		    }
		    c++;
	       }
	  }
	  
	  /* Fin 1 ligne */
	  if( c <= max_col )
	        printf("|///");

	  printf("|\n") ;

	  printf("----");
	  for( c = min_col ; c <= max_col ; c++ )
	       printf("|---");
	  printf("|\n") ;
  
     }

     /* 
      * Pied tableau 
      */

     printf("\n") ;

     return(CORRECT);
}


static
int
terrain_voisins_pos_afficher( coord_t * const liste_voisins ,
			      const int nb_voisins )
{
     int ind_voisin ;
     int l , c ;
     int min_col , max_col ; 

     /*----------*/

     /* 
      * Entete tableau 
      */

     terrain_rech_minmax_x( liste_voisins, nb_voisins,
			    &min_col , &max_col );
     printf("    ");
     for( c = min_col ; c <= max_col ; c++ )
	  printf("|  %2d " , c );
     printf("|\n") ;

     printf("----");
     for( c = min_col ; c <= max_col ; c++ )
	  printf("|-----");
     printf("|\n") ;


     /*
      * Corps tableau 
      */

     ind_voisin=0 ;
     while( ind_voisin < nb_voisins ) 
     {
	  /* Debut 1 ligne */

	  l = liste_voisins[ind_voisin].y ;
	  printf( " %2d " , l ) ;

	  /* Corps 1 ligne */

	  while( (ind_voisin < nb_voisins) &&
		 (l == liste_voisins[ind_voisin].y ) )
	  {
	       c = min_col ;

	       while( (ind_voisin < nb_voisins) &&
		      (l == liste_voisins[ind_voisin].y ) &&
		      ( c <= max_col ) )
	       {
	       
		    if( c == liste_voisins[ind_voisin].x ) 
		    {
			 /* Affichage 1 case */
		      printf("|%5lld" , (long long)liste_voisins[ind_voisin].pos );

			 ind_voisin++ ;
		    }
		    else
		    {
			 printf("|/////");

		    }
		    c++;
	       }
	  }
	  
	  /* Fin 1 ligne */
	  if( c <= max_col )
	       printf("|/////");

	  printf("|\n") ;

	  printf("----");
	  for( c = min_col ; c <= max_col ; c++ )
	       printf("|-----");
	  printf("|\n") ;
  
     }

     /* 
      * Pied tableau 
      */

     printf("\n") ;

     return(CORRECT);
}


extern
int
terrain_voisins_afficher( const int fd ,
			  coord_t * const liste_voisins ,
			  const int nb_voisins )
{
     printf( "Marques des voisins :\n");
     terrain_voisins_marque_afficher( fd , liste_voisins, nb_voisins ) ;

     printf( "Positions des cases dans le fichier :\n");
     terrain_voisins_pos_afficher( liste_voisins , nb_voisins );

     return(CORRECT);
}



/* 
 * Lecture des dimensions du terrain
 */

extern 
int
terrain_dim_lire( const int fd,	/* descripteur fichier terrain */
		  int * nb_lig,	/* nombre de lignes */
		  int * nb_col)	/* nombre de colonnes */
{

     /*----------*/

     /* 
      * Initialisation des resultats 
      */
     (*nb_lig) = 0 ; 
     (*nb_col) = 0 ; 

     /* 
      * Mise de la position courante au debut du fichier
      */

     if( lseek(fd, (off_t)0, SEEK_SET) == -1 )
     {
	  perror("terrain_afficher : Pb lseek debut fichier \n");
	  return(ERREUR) ;
     }

     /* 
      * Lecture des dimensions du terrain 
      */
     
     if( read( fd , nb_lig , sizeof(int)) == -1 )
     {
	  perror("terrain_afficher : Pb read sur lecture nb lignes");
	  return(ERREUR) ;
     }

     if( read( fd , nb_col , sizeof(int)) == -1 )
     {
	  perror( "terrain_afficher : Pb read sur lecture nb colonnes");
	  return(ERREUR) ;
     }

     return(CORRECT);
}


/*
 * Conversion de coordonnees [x,y] en position dans le fichier
 */

extern
int
terrain_xy2pos( const int fd, /* descripteur fichier terrain */
		const int x,  /* abscisse dans le tableau terrain */  
		const int y,  /* ordonnee dans le tableau terrain */
		off_t * pos ) /* position dans le fichier terrain */
{

     int nb_lig ;
     int nb_col ; 

     /*--------------------*/

     /* 
      * Mise de la position courante au debut du fichier
      */

     if( lseek(fd, (off_t)0, SEEK_SET) == -1 )
     {
	  perror("terrain_afficher : Pb lseek debut fichier \n");
	  return(ERREUR) ;
     }

     /* 
      * Lecture des dimensions du terrain 
      */
     
     if( read( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  perror("terrain_afficher : Pb read sur lecture nb lignes");
	  return(ERREUR) ;
     }

     if( read( fd , &nb_col , sizeof(int)) == -1 )
     {
	  perror( "terrain_afficher : Pb read sur lecture nb colonnes");
	  return(ERREUR) ;
     }

     (*pos) = TERRAIN_TAILLE_ENTETE + ( y*TERRAIN_TAILLE_CASE*nb_col ) + (x*TERRAIN_TAILLE_CASE) ;

     return(CORRECT);
}



/*
 * Conversion d'une position dans le fichier en coordonnees [x,y]
 */

extern
int
terrain_pos2xy( const int fd,		/* descripteur fichier terrain */
		const off_t pos,	/* position dans le fichier terrain */
		int * x,		/* abscisse dans le tableau terrain */  
		int * y)		/* ordonnee dans le tableau terrain */

{
     int taille_lig = 0 ;
     int nb_lig = 0 ;
     int nb_col = 0 ;     
     int pos_w = pos - TERRAIN_TAILLE_ENTETE ;

     /*--------------------*/

     /*
      * Initialisation des resultats 
      */

     (*x) = -1 ;
     (*y) = -1 ;

     /* 
      * Mise de la position courante au debut du fichier
      */

     if( lseek(fd, (off_t)0, SEEK_SET) == -1 )
     {
	  perror("terrain_afficher : Pb lseek debut fichier \n");
	  return(ERREUR) ;
     }

     /* 
      * Lecture des dimensions du terrain 
      */
     
     if( read( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  perror("terrain_afficher : Pb read sur lecture nb lignes");
	  return(ERREUR) ;
     }

     if( read( fd , &nb_col , sizeof(int)) == -1 )
     {
	  perror( "terrain_afficher : Pb read sur lecture nb colonnes");
	  return(ERREUR) ;
     }

     taille_lig = nb_col * TERRAIN_TAILLE_CASE ;

     (*y) = (int)(pos_w / taille_lig) ;
     (*x) = (int)(pos_w - ((*y) * taille_lig) ) ;

     return(CORRECT) ;
}


/*
 * Lecture d'une case du terrain
 */ 

extern 
int 
terrain_case_lire( const int fd,	/* descripteur du fichier terrain */
		   const coord_t coord,	/* coordonnees de la case a lire */
		   case_t * contenu )	/* contenu de la case a lire */
{
     char mess[128] ;

     /*--------------------*/

     if( lseek( fd, coord.pos , SEEK_SET) == -1 )
     {
	  sprintf(mess , "terrain_case_lire : Pb lseek sur case [%d,%d](%lld)" ,
		  coord.y, coord.x , (long long)coord.pos );
	  perror(mess) ;
	  return(ERREUR) ;
     }
     
     if( read( fd , contenu , TERRAIN_TAILLE_CASE ) == -1 )
     {
	  sprintf( mess , "terrain_case_lire : Pb read sur lecture de la case [%d,%d](%lld)",
		   coord.y, coord.x , (long long)coord.pos );
	  perror(mess);
	  return(ERREUR) ;
     }

     return(CORRECT);
}
		   
