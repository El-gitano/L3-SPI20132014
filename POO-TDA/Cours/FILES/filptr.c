/*made in Switzerland*/


/* Implantation du TDA FILE par pointeur avec en-tête

    Un objet file est un pointeur sur une structure qui contient
    -un pointeur vers l'ELEMENT
    -la cellule suivante
    
    Les fonctions qui suivent sont valables pour une file circulaire

    Une file est vide ssi  F->suivant = NULL
    
*/

#include "fileprim.h"

#include <stdlib.h>

#include <stdio.h>



 FFILE FileCreer ()	{
 /* renvoie l'adresse d'une structure dont le champ ELEMENT est un pointeur sur une 
 zone memoire de taille ELEMENT */
	FFILE F;
 	
	F=(FFILE)malloc(sizeof(file));
	
	if (! F) {
		
		printf("Fb de memoire") ;
		exit(0) ;
                }
 	F->element=(ELEMENT *)malloc(sizeof(ELEMENT)) ;
	F->suivant =NULL	;
 	return(F);
 }
 	
 int FileVide(FFILE F)	{
	return(F->debut== NULL);
 }

 
 ELEMENT FileSortir(FFILE F)	{
 	/*Renvoie un éément contenant la valeur du premier element de la liste */
	ELEMENT elt  ;
	if (!FileVide(F)) 	{
		FFILE tmp = (FFILE)malloc(sizeof(file));
		tmp = F->suivant->suivant;
		free(F->suivant->suivant);
		ElementAffecter( &elt, tmp->element);
		F->suivant->suivant = tmp->suivant;
 		return(elt);
 	}
	else return (ElementCreer());
 }
 
int FileEntrer(ELEMENT *elt, FFILE F)	{
	
	file * nouvelle = (file*)malloc(sizeof(file));
	
	if(!nouvelle) {
		
		return 0;
 	}
 	else {
 		
 		nouvelle->element = elt;
 		nouvelle->suivant = F->suivant->suivant;
 		F->suivant->suivant = nouvelle;
 		F->suivant = nouvelle;
 		return(1);
 	}
 }
 
 ELEMENT FileDebut(FFILE F)	{
	if (! FileVide(F))
		return( (F->suivant->suivant->element );
		else return (ElementCreer()) ;
 }
 
 void FileDetruire(FFILE F)	{
 	
 	while(F->suivant !=F->suivant->suivant) {
 		
 		FileSortir(F);
 	}
 	FileSortir(F);
 	Free(F);
 }