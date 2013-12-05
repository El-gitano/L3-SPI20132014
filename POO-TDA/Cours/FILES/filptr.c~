/*made in Switzerland*/


/* Implantation du TDA FILE par pointeur avec en-tête

    Un objet file est un pointeur sur une structure qui contient
    -un pointeur vers l'ELEMENT
    -la cellule suivante

    Une file est vide ssi  FFILE->suivant = NULL
    
*/

#include "fileprim.h"

#include <stdlib.h>

#include <stdio.h>



 FFILE FileCreer ()	{
 /* renvoie l'adresse d'une structure dont le champ ELEMENT est un pointeur sur une 
 zone memoire de taille ELEMENT */
	FFILE p;
 	
	p=(FFILE)malloc(sizeof(file));
	
	if (! p) {
		
		printf("pb de memoire") ;
		exit(0) ;
                }
 	p->element=(ELEMENT *)malloc(sizeof(ELEMENT)) ;
	p->suivant =NULL	;
 	return(p);
 }
 	
 int FileVide(FFILE P)	{
	return(P->debut== NULL);
 }

 
 ELEMENT FileSortir(FFILE P)	{
	ELEMENT elt  ;
	if (!FileVide(P)) 	{
		ElementAffecter( &elt, (P->suivant->suivantelement));
		P->debut = (P->debut + 1) % P->longMax;
 		return(elt);
 	}
	else return (ElementCreer());
 }
 
int FileEntrer(ELEMENT elt, FFILE P)	{
 	if(! FilePleine( P))	{
		 P->fin = (P->fin + 1) % P->longMax;
		ElementAffecter( &(P->elements)[P->fin], elt);
 		return(1);
 	}
 	else {
		printf("FFILE pleine\n");
 		return(0);
 	}
 }
 
 ELEMENT FileDebut(FFILE P)	{
	if (! FileVide(P))
		return( (P->elements)[P->debut] );
		else return (ElementCreer()) ;
 }
 
 void FileDetruire(FFILE P)	{
 	free(P->elements);
 	free(P);
 }

 void FileAfficher (FFILE P) {
	int i ;
	if (! FileVide(P))
		if (P->debut <= P->fin)
			for (i = P-> debut ; i <= P -> fin; i ++ )
				ElementAfficher(P -> elements [i]) ;
		else
		    for (i = P-> debut ; i <= (P -> fin + P->longMax); i++  )
			ElementAfficher(P -> elements [i% P->longMax]) ;
}

void FileRadiographier(FFILE P) {
	int i ;
	printf("\n debut : %d  , fin : %d", P->debut, P->fin) ;
	for (i = 0 ; i <= P -> longMax -1 ; i++)  {
		printf("\n indice : %d , element : ",i) ;
		ElementAfficher(P -> elements [i]) ;
		}
}
