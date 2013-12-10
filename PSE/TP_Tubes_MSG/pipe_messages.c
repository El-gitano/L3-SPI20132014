#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <pipe_messages.h>


/*
 * Affichage d'un message 
 */
extern
void
pipe_afficher( char * const message )
{
     int i;

     for(i=0 ; i<MESSAGES_TAILLE ; i++ )
     {
	  if( i % 80 == 0 ) 
	  {
	       printf("\n");
	  }
	  printf("%c" , message[i] );
     }
     printf("\n");
}

/*
 * Remplissage d'un message 
 */
extern
void
pipe_remplir( char * message , const char val )
{
     int i ;

     for(i=0 ; i<MESSAGES_TAILLE ; i++ )
     {
	  message[i] = val ;
     }

}


