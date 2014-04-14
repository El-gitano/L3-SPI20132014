#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>


/*Le code source contient entre autres
-Identificateurs (JULES)*/
#define IDENT -1

/*-Entier (547)*/
#define ENT -2

/*-Reels 35.42*/
#define REEL -3 

/*-FF*/
#define FF -4

/*-Autres*/
#define OTH -5

#define MAX 220

typedef struct lexeme{
	int valeur;
	int classe;
}lexeme_t;


lexeme_t ChaineLex[10];	/*chaine lexicale*/
char chaine[MAX];		/*Stockage des identificateurs avant empilage dans la chaine lexicale*/
int entier;				/*Entier utilisé pour stocker les entiers reconnus*/
float reel;				/*Float utilisé pour stocker les réels*/
int nbredec;			/* nbre de chiffre derrière la virgule*/

int Idx0;
int Idx1;

int Etat;				/*recupérateur de l'état*/
int Classe;				/*Récupérateur de la classe*/
char c;					/*caractère de récup*/
int i;					/*Compteur général pour le code source*/
int j;					/*Compteur pour le tableau de lexeme*/
int compteur;			/*Compteur pour des trucs et d'autres*/

int AEF[10][10];

char text[MAX];

char LireCar(){

	return text[i];
}

int isFF(char c){

	if(c == '\\')
	
		return 1;
	else
	 
		return 0;
}

int ClasseChar(char c){
	
	if(isalpha(c)){
	
		return 1;
	}
	else if(isdigit(c)){
		
		return 2;
	}
	
	else if(c =='.' || c == ','){
		
		return 3;
	}
	
	else if(isFF(c)){
		
		return 4;
	}
	else if(c == '\0'){
		return 4;
	}
	
	else {
		return 5;
	}
}


void AlexAmorcer(){

/* On amorce l'AEF*/
/*Première ligne, etat initial*/
AEF[0][1] = 1;	//Identifiant en cours
AEF[0][2] = 2;	//Entier en cours
AEF[0][3] = -5;	//Autre
AEF[0][4] = -4;	//Fin de fichier
AEF[0][5] = -5;	//Autre

/*Deuxième ligne : identifiant en cours*/
AEF[1][1] = 1;
AEF[1][2] = -1;
AEF[1][3] = -1;
AEF[1][4] = -1;
AEF[1][5] = -1;

/*Troisième ligne : entiers en cours*/
AEF[2][1] = -2;
AEF[2][2] = 2;
AEF[2][3] = 4;		//Ligne particulière : passage d'un entier à un reel, donc traitement particulier
AEF[2][4] = -2;
AEF[2][5] = -2;

/*Quatrième ligne : reel en cours*/
AEF[3][1] = -3;
AEF[3][2] = 3;
AEF[3][3] = -3;
AEF[3][4] = -3;
AEF[3][5] = -3;


}

void AlexInitialiser(){

//Initialisation des toutes les variables avant reconnaissance de la chaine Lexicale
	Etat = 0;
	entier = 0;
	reel = 0.0;
	nbredec = 0;
	i = 0;
	j = 0;
	Idx0 =0;
	Idx1 = 0;
}

void AlexReconnaitre(){

/*Initialisaton de l'etat et des variables*/
	AlexInitialiser();
	
	do {
	
		c = LireCar();				//Récupération du caractère a analyser
		Classe = ClasseChar(c);		//Analyse de la classe
		Etat = AEF[Etat][Classe];	//Analyse de l'etat en fonction de l'etat précédent et de la classe obtenue
		
		printf("Caractère lu : %c; classe déduite : %i; Etat déduit : %i\n", c, Classe, Etat);
		
		if(Etat < 0){
		
			switch(Etat){
			
				case -1	:
				
					ChaineLex[j].valeur = c;
					ChaineLex[j].classe = 1;
					Etat  = 0;
					j +=1;
					printf("Identifiant reconnu : %s \n", chaine);
					Idx0 = 0;
					chaine[0] = '\0';
					break;
					
				case -2 :
				
					ChaineLex[j].valeur = entier;
					ChaineLex[j].classe = 2;
					printf("Entier reconnu : %d \n", entier);
					entier = 0;
					j+=1;
					Etat = 0;
					break;
					
				case -3 :
				
					for(compteur = 0; compteur < nbredec; compteur ++){
					
						reel * 10.0;
						
					}
					
					ChaineLex[j].valeur = reel;
					ChaineLex[j].classe = 3;
					printf("Reel reconnu : %f\n", reel);
					nbredec = 0;
					reel = 0;
					Etat = 0;
					j +=1;
					break;
					
				case -4 :
				
					printf("Fin de Fichier\n");
					break;
					
				case -5 :
				
					printf("Erreur rencontrée : %c n'était pas attendu\n", c);
					i +=1;
					break;
			}
		}
		else {
			switch(Etat){
			
				case 1 :
					chaine[Idx0] =c;
					Idx0 +=1;
					break;
					
				case 2 :
					entier = entier * 10 + (c - '0');
					break;
					
				case 3 :
					nbredec +=1;
					reel += (c-'0')/(pow(10.0, nbredec));
					printf("reel = %f\n", reel);
					break;
				
				case 4 :
					reel = entier * 1.0;
					entier = 0;
					Etat = 3;
					break;
					
			}
		
			i += 1;
		}
	}while(Etat != -4);
}

void AlexTester(int nJeton){

	switch(nJeton){
	
		case 1 :
			strcpy(text, "totoestleplusgrand");
			break;
			
		case 2 :
			strcpy(text, "11Truc11.2echap");
			break;
			
		case 3 :
			strcpy(text, "");
			break;
			
		case 4 : 
			strcpy(text, "1111,11.d1d42");
			break;
			
		case 5 :
			strcpy(text, "");
	}
	AlexAmorcer();
	printf("Le texte est : %s\n", text);
	AlexReconnaitre();
	
}
