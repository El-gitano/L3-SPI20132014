#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <msg_messages.h>


/*
 * Affichage d'un message 
 */
extern
void
msg_afficher( message_t * const message )
{
     int i;

  /* Type du message */ 
  printf("\tType = %ld\n" , message->type) ; 

  /* Corps */
  printf("\tCorps =\n") ;
  for(i=0 ; i<MESSAGES_TAILLE ; i++ )
  {
       if( i % 80 == 0 ) 
       {
	    printf("\n");
       }
       printf("%c" , message->corps.buffer[i] );
  }
  printf("\n");
}

/*
 * Remplissage d'un message 
 */
extern
void
msg_remplir( message_t * message , const char val )
{
     int i ;

     /* Type du message */ 
     message->type = MSG_TYPE_RECEPTEUR ;

     /* Corps */
     for(i=0 ; i<MESSAGES_TAILLE ; i++ )
     {
	  message->corps.buffer[i] = val ;
     }

}


