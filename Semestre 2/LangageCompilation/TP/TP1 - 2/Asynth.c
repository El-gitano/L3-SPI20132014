#include <stdio.h>
#include <stdlib.h>
#include "Asynth.h"

int bProgramme(int, int *);
int bCode(int, int *);
int bLigne(int, int *);
int bIdt(int, int *);
int bFF(int, int *);
int bReel(int, int *);

//int classeAssociee[10] = {5};
//int classeAssociee[10] = {1, 3, 1, 5};
//int classeAssociee[10] = {1, 4, 1, 3, 1, 5};
//int classeAssociee[10] = {1, 3, 1, 3, 1, 3, 1, 3, 5};

int bProgramme(int iD, int *piF){
	//Programme -> Code
	
	int bSucces;
	int iF;

	//On effectue nos opérations
	bSucces = bCode(iD, &iF);

	*piF = (bSucces) ? iF : iD;
	return bSucces;	
}

int bCode(int iD, int *piF){
	//Code -> FinFichier + Ligne.Code
	int bSucces;
	int iS,iF;
	int resBFF;
	
	resBFF = bFFeclaireur(iD);
	
	if(resBFF){
	
		bSucces = bFF(iD, &iF);
	}
	else{
	
		bSucces = (bLigne(iD, &iS) && bCode(iS, &iF));
	}

	*piF = (bSucces) ? iF : iD;
	return bSucces;	
}

int bLigne(int iD, int *piF){
	//Ligne -> Identificateur.Réel
	int bSucces;
	int iS,iF;

	//On effectue nos opérations
	bSucces = bIdt(iD, &iS) && bReel(iS, &iF);

	*piF = (bSucces) ? iF : iD;
	return bSucces;	
}

int bIdt(int iD, int *piF){

	int bSucces;

	//On effectue nos opérations
	bSucces = bAlexIdentIdt(iD);

	*piF = (bSucces) ? iD+1 : iD;
	return bSucces;	
}

int bReel(int iD, int *piF){

	int bSucces;

	bSucces = bAlexIdentReel(iD);

	*piF = (bSucces) ? iD + 1 : iD;
	return bSucces;	
}

int bFF(int iD, int *piF){

	int bSucces;

	bSucces = bAlexIdentFF(iD);

	*piF = (bSucces) ? iD + 1 : iD;
	return bSucces;	
}

void AsyntAmorcer(){


}

void AsyntInitialiser(){


}

void AsyntTester(int iNb){

	int sortie = 0;
	
	if (bProgramme(0, &sortie)){
	
		printf("\nChaîne lexicale reconnue (sortie = %i)\n", sortie);
	}
	else{
	
		printf("\nChaîne lexicale non reconnue (sortie = %i)\n", sortie);
	}
}


