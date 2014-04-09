#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Asynt.h"
#include "Alex.h"


int bFF(int eD, int *peF){

	printf("Appel a bAlexFF, resultat : ");
	int bSucces = bAlexFF(eD);
	*peF = (bSucces)? eD+1:eD;
	printf("%i\n", bSucces);
	return(bSucces);
}

int bIdent(int eD, int *peF){

	printf("Appel a bAlexIdent, resultat : ");
	int bSucces = bAlexIdent(eD);
	*peF = (bSucces)? eD+1:eD;
	printf("%i\n", bSucces);
	return (bSucces);
}

int bReel(int eD, int *peF){
	
	printf("Appel a bAlexReel, resultat : ");
	int bSucces = bAlexReel(eD);
	*peF = (bSucces)? eD+1:eD;
	printf("%i\n", bSucces);
	return(bSucces); 
}
int bLigne(int eD, int *peF){
	
	//Ligne -> Ident.Reel
	int bSucces, eF, eR;
	bSucces = bIdent(eD, &eR) && bReel(eR, &eF);
	*peF =(bSucces)? eF:eD;
	return (bSucces);
}

//Regle pour reconnaitre du Code
int bCode(int eD, int *peF){
	
	//Code -> FF + Ligne.Code
	int bSucces, eF, eI, bF;
	if(bF = bAlexFF(eD))
		bSucces = bF;
	else
		bSucces = (bLigne(eD, &eI) && bCode(eI, &eF));
	
	*peF =(bSucces)? eF:eD;	
	return (bSucces);
}


//Regle pour reconnaitre Prog
int bProg(int eD, int *peF){
	
	//Prog -> Code
	int bSucces, eF;
	bSucces = bCode(eD, &eF);
	*peF =(bSucces)? eF:eD;
	return (bSucces);
}

int AsyntTester(){

	int eF = 0;
	int bSucces =  bProg(0, &eF);
		
	if(bSucces)
		printf("All Right!\n");

	printf("Fin des tests\n\n");
	return EXIT_SUCCESS;
}
