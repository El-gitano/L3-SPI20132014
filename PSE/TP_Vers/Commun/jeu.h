#ifndef _JEU_H_
#define _JEU_H_

#include <vers.h>

/*
 * Initialisation de la tete d'un ver dans le terrain de jeu
 * renvoi les coordonnees d'une case libre choisie aleatoirement
 * Pour utiliser cette fonction il faut que :
 * - la structure ver soit creee
 * - la marque du ver soit affectee
 * La fonction renvoie ERREUR s'il elle ne peut trouver une case libre dans le terrain
 */

extern 
int jeu_ver_initialiser( const int fd_terrain, /* Fichier terrain */
			 const int nb_lig, /* dimensions terrain */
			 const int nb_col, 
			 ver_t * ver );  /* ver a initialiser */

#endif
