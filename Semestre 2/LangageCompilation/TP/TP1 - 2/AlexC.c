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
#define TAILLEX 12

//Définition des lexemes
typedef struct lexeme{
	float valeur;
	int classe;
}lexeme_t;


//Déclaration de toutes les variables globales
lexeme_t ChaineLex[TAILLEX];	/*chaine lexicale*/
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

int TDS[26][2];



//Fonction lireCar, renvoyant un caractere
char LireCar(){

	return text[i];
}

//Fonction isFF, prenant un caractere en paramatre, renvoyant s'il s'agit de la fin de fichier
int isFF(char c){

	if(c == '\\' || c=='\0')
	
		return 1;
	else
	 
		return 0;
}

//Fonction ClasseChar, prenant un char en parametre et renvoyant un entier correspondant a sa classe
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
	
	else {
		return 5;
	}
}

int bAlexIdent(int e){
	
	int bSucces = ((ChaineLex[e].classe == 1) && e < j);
	return bSucces;
}

int bAlexFF(int e){

	int bSucces = ((ChaineLex[e].classe == 4) && e >= j);
	return bSucces;
}

int bAlexReel(int e){

		int bSucces = ((ChaineLex[e].classe == 3) && e < j);
		return bSucces;
}

int bTDSajouter(int rangReel){
	

	if(TDS[(int)ChaineLex[rangReel-1].valeur][0] > 0){
		
		TDS[(int)ChaineLex[rangReel-1].valeur][1] = rangReel;
	}
	else if(TDS[(int)ChaineLex[rangReel-1].valeur][1] < 0)  {
	
		TDS[(int)ChaineLex[rangReel-1].valeur][0] = rangReel;
	}
	else {
	
		printf("erreur : plus de deux entrée pour le TDS %.0f\n", ChaineLex[rangReel-1].valeur);
	}
	return 1;
}

int bTDSvoir(){
	
	int k = 0;
	for(; k < 26; k ++){
		
		if(TDS[k][1] > 0){
			
			printf("%c  %.2f  %.2f\n", k+65, ChaineLex[TDS[k][0]].valeur, ChaineLex[TDS[k][1]].valeur);
		}
	}
	return 1;
}

int bTDSgenererCode(){
	
	FILE *fichier;
	fichier = fopen("code.c", "w");
	
	if(fichier == NULL){
	
		printf("Le fichier n'existe pas");
	}
	else{
		fprintf(fichier, "#include <stdlib.h>\n");
		fprintf(fichier, "#include <stdlib.h>\n\n");
		fprintf(fichier, "int main(){\n\n");
		
		int k = 0;
		for(; k < 26; k ++){
		
			if(TDS[k][0] > 0){
			
				
				fprintf(fichier, "\tprintf(\"%c  %.2f\\n\");\n", k+65, ChaineLex[TDS[k][1]].valeur - ChaineLex[TDS[k][0]].valeur);
			}
		}
		fprintf(fichier, "\treturn 1;\n");
		fprintf(fichier, "}");
		
	}
	fclose(fichier);
	
	return 1;
}

//Amorçage de l'AEF
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


//Initialisation des variables
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
	
	int k = 0;
	for(; k < 26; k ++){
		
		TDS[k][0] = -1;
		TDS[k][1] = -1;
	}
}

void AlexReconnaitre(){

/*Initialisaton de l'etat et des variables*/
	AlexInitialiser();

	do {
	
		c = LireCar();				//Récupération du caractère a analyser
		Classe = ClasseChar(c);		//Analyse de la classe
		Etat = AEF[Etat][Classe];	//Analyse de l'etat en fonction de l'etat précédent et de la classe obtenue
		
		//printf("Caractère lu : %c; classe déduite : %i; Etat déduit : %i\n", c, Classe, Etat);
		
		if(Etat < 0){
		
			switch(Etat){
			
				case -1	:
				
					ChaineLex[j].valeur = chaine[0]-65;
					ChaineLex[j].classe = 1;
					Etat  = 0;
					j +=1;
					printf("Identifiant reconnu : %s, valeur : %.0f \n", chaine, ChaineLex[j-1].valeur);
					Idx0 = 0;
					memset (chaine, 0, sizeof (chaine));
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
					
					ChaineLex[j].valeur = -1;
					ChaineLex[j].classe = 4;
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
			strcpy(text, "TOTO11.2ALI11.5TOTO22.0ALI24.5");
	}
	AlexAmorcer();
	printf("Le texte est : %s\n", text);
	AlexReconnaitre();
	
}
