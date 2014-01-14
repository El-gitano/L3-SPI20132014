#include <stdio.h>
#include <unistd.h>
#include <messages.h>

extern
void
messages_afficher_etat( const etat_coureur_t etat ) 
{
  switch( etat ) 
    {
    case ARRIVE : 
      printf("ARRIVE") ;
      break ;
    case EN_COURSE :
      printf("EN COURSE") ;
      break ;
    case DECANILLE :
      printf("DECANILLE") ;
      break ;
    default :
      printf("<inconnu (%d)>" , etat ) ;
      break ;
    }
}


static 
void
messages_afficher_type( int type )
{
  switch(type)
    {
    case PC_COURSE : 
      printf("PC_COURSE") ;
      break ;
    default :
      printf("%d" , type) ;
      break ;
    }

}

/*
 * Affichage d'un message de requete d un coureur au PC Course 
 */
extern
void
messages_afficher_requete( requete_t * const requete )
{
  
  /* Type du message */ 
  printf("\tType = ") ; messages_afficher_type(requete->type) ; printf("\n"); 

  /* Corps */
  printf("\tDossard = %d\n\n" , requete->corps.dossard ) ; 
}

/* 
 * Affichage d'un message de reponse du PC Course 
 */
extern
void
messages_afficher_reponse( reponse_t * const reponse )
{
  int i ;

  /*----------*/

  /* Type du message */ 
  printf(" Type = ") ; messages_afficher_type(reponse->type) ; printf("\n"); 

  /* Corps */

  /* -- Arrivee */
  printf(" Etat = ");  messages_afficher_etat( reponse->corps.etat ) ; printf("\n"); 

  /* -- Nombre de coureurs */
  printf("\nNombre de coureurs = %d\n" , reponse->corps.nb_coureurs );

  /* -- Entete classement */
  if( reponse->corps.nb_coureurs > 0 ) 
  {
       printf("\t*---------*----------*\n" );
       printf("\t| Dossard | Distance |\n" );
       printf("\t*---------*----------*\n" );
       /* -- Classement */
       for( i=0 ; i < reponse->corps.nb_coureurs ; i++)
       {
	    printf( "\t|  %5d  |      %3d |\n" , 
		    reponse->corps.tab_coureurs[i].dossard ,  
		    reponse->corps.tab_coureurs[i].distance );
       }
       /* -- Pied classement */
       printf("\t*---------*----------*\n\n" );
  }
}

/* 
 * Affichage du parcours de la course
 */
extern
void
messages_afficher_parcours( reponse_t * const reponse )
{
     int km ; 
     pid_t moi = getpid() ; 
     int ind_coureur  = 0 ;

     /*----------*/


     printf("-*-" ) ; for( km=DISTANCE ; km > 0; km--) printf("-") ; printf("---\n" );

     printf(" | " ) ;
     ind_coureur  = 0 ;
     km=DISTANCE ;
     while( (km > 0) && (ind_coureur < reponse->corps.nb_coureurs) )
     {
	  if( reponse->corps.tab_coureurs[ind_coureur].distance == km ) 
	  {
	       /* Il y a un coureur a cet endroit du parcours */
	       if( reponse->corps.tab_coureurs[ind_coureur].dossard == moi ) 
	       {
		    /* C'est ce processus */
		    printf("X");
	       }
	       else
	       {
		    /* C'est un autre coureur */
		    printf("O") ;
	       }
	       /* Saut des ex-aequos */
	       while(reponse->corps.tab_coureurs[ind_coureur].distance == km )
		    ind_coureur++ ;
	  }
	  else
	  {
	       /* Il n'y a pas de coureur a cet endroit */
	       printf( " " );
	  }
	  km -- ;
     }

     /* En principe, il ne reste plus de coureurs */
     while( km > 0 )
     {	  
	  printf( " " );
	  km -- ;
     }

     printf(" | \n" ) ;
     printf("-*-" ) ; for( km=DISTANCE ; km > 0; km--) printf("-") ; printf("---\n" );
}

/*
 * Initialisation de l'attente 
 */
extern
void
messages_initialiser_attente() 
{
  srandom(getpid()) ;
}

/* 
 * Attente entre 2 envois de message vers le PC Course 
 */
extern
void
messages_attendre_tour() 
{
  sleep(random()%10) ;
}
