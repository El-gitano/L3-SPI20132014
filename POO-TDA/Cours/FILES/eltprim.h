/*****************************************************************
*		Fichier :  	ELTPRIM.H
*		Format :	Source C 
*		Version  : 	19/9/96
*		Programmeurs :	Delozanne/Jacoboni , Futtersack
*		Contenu :      	Déclaration des primitives du TDA ELEMENT.
*		
******************************************************************/

#ifndef _ELTPRIM_H                   /* pour l'inclusion conditionnelle */
#define  _ELTPRIM_H

/* inclusion de la déclaration du type concret ELEMENT */
#include "eltsdd.h"

/*  Déclaration des primitives du TDA ELEMENT

Déclaration du type auxiliaire bool */

typedef enum {FAUX, VRAI} bool ;


/* Déclaration des primitives du TDA ELEMENT */

void ElementLire(ELEMENT *);
void ElementAfficher(ELEMENT);
ELEMENT ElementAffecter(ELEMENT*, ELEMENT);
	/* affecte le deuxieme argument dans le premier
	qui est donc modifié et passé par adresse */
bool ElementIdentique(ELEMENT, ELEMENT);
	/* retourne vrai si les deux arguments sont identiques */

/* Primitives inutiles pour le stockage direct, Mais obligatoire en
   stockage indirect */

ELEMENT ElementCreer() ;
void ElementDetruire(ELEMENT) ;

#endif
