/******************************************************************
*		Fichier :  	FILEPRIM.H
*		Format :	Source C 
*		Version  : 	21/9/96
*		Programmeurs :	Delozanne/Jacoboni
*		Contenu :      	Déclaration des primitives du TDA FILE
*				(indépendant de la représentation)
******************************************************************/


#ifndef FILEPRIM_H                    /* pour inclusion conditionnelle */
#define FILEPRIM_H

#include "eltprim.h" 			/* le TDA FILE utilise le TDA ELEMENT */

#include "filesdd.h"			/*   inclure le type concret Pile */


FFILE FileCreer (int profondeur) ;
	/* crée et retourne une file vide en lui allouant dynamqiuement de la mémoire */
void FileDetruire(FFILE);
	/* libère la mémoire allouée pour la file */

int FileVide(FFILE);
	/* teste si la file est vide */

ELEMENT FileDebut(FFILE);
	/* retourne l'élément au début de la file sans le retirer de la file */

ELEMENT FileSortir(FFILE);
	/* retourne l'élément au début de la file en le retirant de la file */
int FileEntrer(ELEMENT, FFILE);
	/* place l'élément à la fin de la file */

void FileAfficher (FFILE ) ; /* pour test et mise au point */
void FileRadiographier(FFILE P) ;

/* void FileRaz(FFILE) ;
   void FileNettoyer(FFILE) ;  ça peut être utile à faire en exercice */

#endif
