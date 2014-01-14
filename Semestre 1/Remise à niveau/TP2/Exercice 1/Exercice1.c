/*
 * auteur : ANTOINE FOUCAULT
 * version 0.1 : Date : Fri Sep 20 09:05:05 CEST 2013
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ENTREES 500

typedef struct{

	char *mot;
	int lignes[50];
	int nbLignes;
}Entree;

typedef struct{

	Entree entrees[MAX_ENTREES];
	int nbEntrees;
}Table;

void initTable(Table *t){
	
	t->nbEntrees=0;
}

void initEntree(Entree *t, char *mot,int numLigne){

	//On alloue l'espace pour le mot en mémoire dynamique
	t->mot=(char *)malloc(sizeof(char)*strlen(mot));
	strcpy(t->mot,mot);

	//Vu qu'on a un nouveau mot on initialise le nombre de lignes à 0
	t->nbLignes=0;
	t->lignes[t->nbLignes++]=numLigne;
}

void ajouterLigne(Entree *t, int numLigne){

	t->lignes[t->nbLignes]=numLigne;
	t->nbLignes++;
}

int rechercheEntree(Table *t, char *mot){

	int i;

	//On parcours la table à la recherche de la chaine
	for(i=0;i < t->nbEntrees;i++){

		if(strcmp(mot,t->entrees[i].mot)==0){

			//On retourne l'indice de l'entrée
			return i;
		}
	}

	//Recherche infructueuse
	return -1;
}

void traiterMot(Table *t, char *mot, int numLigne){

	int res;
	
	/*Si le mot existe dans la table*/
	if(res=rechercheEntree(t,mot)>0){

		ajouterLigne(&(t->entrees[res]), numLigne);
	}
	/*Sinon*/
	else if(t->nbEntrees<MAX_ENTREES){

		initEntree(&(t->entrees[t->nbEntrees]), mot, numLigne);
		t->nbEntrees++;
	}
}

//Pour chaque entrée on affiche le mot ainsi que ses lignes à l'aide de boucles
void afficheTable(Table *t){

	int i,j;

	//Boucle des entrées
	for(i=0;i < t->nbEntrees;i++){

		printf("%s : ",t->entrees[i].mot);

		//Boucles des lignes
		for(j=0;j < t->entrees[i].nbLignes;j++){

			printf("[%i]",t->entrees[i].lignes[j]);
		}

		printf("\n");
	}	
}

//On parcours les entrées et on free les mots qui ont été alloués dynamiquement
void supprimerTable(Table *t){

	int i,j;

	for(i=0;i < t->nbEntrees;i++){
		
		fprintf(stderr,"%i",i);
		free(&(t->entrees[i].mot));
		t->entrees[i].nbLignes=0;
	}

	t->nbEntrees=0;
}

int main(){

	Table maTable;
	char c;
	char mot[80];
	int imot=0;
	int numLigne=0;
	initTable(&maTable);

	while((c=getchar())!=EOF){

		if(isalpha(c)){
			mot[imot++]=c;
			
		}
		else{
			
			mot[imot]='\0';
						
			if(imot>0){

				traiterMot(&maTable, mot, numLigne);
			}
			imot=0;
		}
		if(c=='\n'){
			numLigne++;
		}
	}

	afficheTable(&maTable);

	supprimerTable(&maTable);
	
	return EXIT_SUCCESS;
}
