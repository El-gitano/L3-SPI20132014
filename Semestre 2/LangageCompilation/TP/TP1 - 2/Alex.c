#include <stdio.h>
#include <stdlib.h>
#include "Alex.h"

long creerValeurIdentifiant(int *, int *);
long creerValeurReel(int *, int *);
long creerValeurAutre(int *, int *);
long creerValeurEntier(int *, int *);
void ajouterLexeme(long, int);
int classeCar(char);
int bIndexCorrect(int);

//Variables de parcours du code source et "code source"
int pos = 0;
int posTemporaire = 0;

//Chaînes pour les tests
//char texte[] = "TOTOestle12.78plus12 beau n'est-ce pas ? tout 23 à FE 23.12 34";
//char texte[] = "";
//char texte[] = "81.54";
char texte[] = "TOTO9.42TATA1.21TUTU1.1";

//Chaîne lexicale résultante de l'analyse syntaxique + taille
long valeurs[SIZE_TAB];
int classeAssociee[SIZE_TAB];
int positionChaineLexicale = 0;

int Etat = 1;
int AEF[6][6];//L'AEF est définit dans AlexAmorcer()

int bIndexCorrect(int ind){

	return (ind < positionChaineLexicale && ind >= 0);
}

int bAlexIdentReel(int ind){

	printf("Je passe par %li\n", valeurs[ind]);
	return (bIndexCorrect(ind) && (classeAssociee[ind] == 3));
}

int bAlexIdentIdt(int ind){

	printf("Je passe par %li\n", valeurs[ind]);
	return (bIndexCorrect(ind) && (classeAssociee[ind] == 1));
}

int bFFeclaireur(int ind){

	int retour;
	
	if(ind >= positionChaineLexicale){
	
		retour = 1;
	}
	else{
	
		retour = (bIndexCorrect(ind) && (classeAssociee[ind] == 5));
	}
	
	return retour;
}

int bAlexIdentFF(int ind){
	
	printf("Je passe par la fin de fichier\n");
	int retour;
	
	if(ind >= positionChaineLexicale){
	
		retour = 1;
	}
	else{
	
		retour = (bIndexCorrect(ind) && (classeAssociee[ind] == 5));
	}
	
	return retour;
}

char lireCar(){//Le dépassement de lecture de la chaîne n'est pas géré

	return (texte[posTemporaire++]);
}

int classeCar(char c){

	if(isdigit(c)){//Caractère numérique
	
		return 3;
	}
	else if(c == '.'){//Séparateur de nombre
	
		return 2;
	}
	else if (isupper(c)){//Caractère majuscule
	
		return 1;
	}
	else if(c == '\0'){ //FF
	
		return 4;
	}
	else{//Autre (minuscules et espaces notamment)
	
		return 5;
	}
}

void AlexAmorcer(){//Init AEF avec en lignes les états et en colonne [A-Z] | . | [0-9] | FF | Autre

	AEF[1][1] = 2;
	AEF[1][3] = 3;
	AEF[1][4] = -5;
	AEF[1][5] = 5;
	
	AEF[2][1] = 2;
	AEF[2][2] = -1;
	AEF[2][3] = -1;
	AEF[2][4] = -1;
	AEF[2][5] = -1;
	
	AEF[3][1] = -2;
	AEF[3][2] = 4;
	AEF[3][3] = 3;
	AEF[3][4] = -2;
	AEF[3][5] = -2;
	
	AEF[4][1] = -3;
	AEF[4][2] = -3;
	AEF[4][3] = 4;
	AEF[4][4] = -3;
	AEF[4][5] = -3;
	
	AEF[5][1] = -4;
	AEF[5][2] = -4;
	AEF[5][3] = -4;
	AEF[5][4] = -4;
	AEF[5][5] = 5;
}

void AlexInitialiser(){


}

void AlexReconnaitre(){

	do{
	
		//Parcours de la chaîne texte
		char car = lireCar();	
		int classe = classeCar(car);
		Etat = AEF[Etat][classe];

		if(Etat <= 0){
		
			switch(Etat){
						
				case -1://Empile un identificateur
				
					ajouterLexeme(creerValeurIdentifiant(&pos, &posTemporaire), 1);
					break;
					
				case -2://Empile un entier
				
					ajouterLexeme(creerValeurEntier(&pos, &posTemporaire), 2);
					break;
					
				case -3://Empile un réel
				
					ajouterLexeme(creerValeurReel(&pos, &posTemporaire), 3);
					break;
					
				case -4://Empile un "Autre"
				
					ajouterLexeme(creerValeurAutre(&pos, &posTemporaire), 4);
					break;	
					
				case -5://Empile une fin de ficher
				
					ajouterLexeme(0, 5);
					break;
			}
			
			//On réutilise le caractère consommé afin de relancer l'identification d'un nouveau lexème
			Etat = AEF[1][classe];
		}
	
	}while(Etat > 0);
	
	ajouterLexeme(0, 5);
}

void AlexTester(int iNb){

	
}

long creerValeurIdentifiant(int *position, int *positionTemp){

	//printf("Appel à creerValeurIdentifiant\n");
	
	long valeur = 0;
	
	for(;*position < (*positionTemp - 1); *position = *position+1){
	
		valeur *= 26 ;
		valeur += texte[*position] - 'A';
	}
	
	return valeur;
}

long creerValeurEntier(int *position, int *positionTemp){

	//printf("Appel à creerValeurEntier\n");
	
	long valeur = 0;
	
	for(;*position < (*positionTemp - 1); *position = *position+1){
	
		valeur *= 10;
		valeur += texte[*position] - '0';
	}
	
	return valeur;
}

long creerValeurReel(int *position, int *positionTemp){//Effectuer le traitement par rapport au point

	//printf("Appel à creerValeurReel\n");	
	
	long valeur = 0;
	
	for(;*position < (*positionTemp - 1); *position = *position+1){
	
		if(texte[*position] != '.'){
		
			valeur *= 10;
			valeur += texte[*position] - '0';
		}
	}
	
	return valeur;
}

long creerValeurAutre(int *position, int *positionTemp){//Effectuer le traitement par rapport au point

	//printf("Appel à creerValeurAutre\n");	
	
	long valeur = 0;
	
	for(;*position < (*positionTemp - 1); *position = *position+1){
	
		valeur *= 128;
		valeur += texte[*position];
	}
	
	return valeur;
}

void ajouterLexeme(long valeur, int classe){
	
	valeurs[positionChaineLexicale] = valeur;
	classeAssociee[positionChaineLexicale++] = classe;
}

void lireChaineLexicale(){

	int i;
	
	printf("\n");
	
	for(i=0 ; i<positionChaineLexicale; i++){
	
		printf("%ld - ", valeurs[i]);
		
		switch(classeAssociee[i]){
		
			case 1:
			
				printf("identificateur");
				break;
				
			case 2:
			
				printf("entier");
				break;
				
			case 3:
			
				printf("réel");
				break;
				
			case 4:
			
				printf("autre");
				break;
				
			case 5:
			
				printf("fin de fichier");
				break;
		}
		
		printf("\n");
	}
	
	printf("\n");
}