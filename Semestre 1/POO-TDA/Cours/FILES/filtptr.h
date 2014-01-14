/*Made In Switzerland*/


/* Realisation du TDA FILE par pointeur

    Un objet file est un pointeur sur une structure cellule qui contient
    -Un pointeur vers un ELEMENT
    * un pointeur vers la cellule suivante dans la file.
    
*/
#ifndef FILTABCI_H
#define FILTABCI_H


typedef struct cellule {
 	ELEMENT *element ;
	struct cellule *suivant;
 } file,	*FFILE ;
 

#endif





