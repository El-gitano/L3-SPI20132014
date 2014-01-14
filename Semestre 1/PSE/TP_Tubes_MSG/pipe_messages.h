#ifndef _MSG_MESSAGES_H_
#define _MSG_MESSAGES_H_

#include <messages.h>

#define NOM "TUBE"

/*
 * Definition des fonctions 
 */

/* Affichage d'un message */
extern
void pipe_afficher( char * const message );

/* Remplissage d'un message */
extern
void pipe_remplir( char * message , const char val ) ;

#endif
