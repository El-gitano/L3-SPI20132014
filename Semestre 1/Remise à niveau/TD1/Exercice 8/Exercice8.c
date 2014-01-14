#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

int main(){
	
	int nb_lignes,nb_etoiles=1,nb_espaces,i;
	
	do{
	
		printf("Veuillez entrer le nombre de lignes : ");
		scanf("%i",&nb_lignes);
		vider_buffer_stdin();
	}while(nb_lignes<1);
	
	nb_espaces=nb_lignes-1;

	while(nb_lignes>0){
	
		i=nb_espaces;
		while(i>0){
			printf(" ");
			i--;
		}
		
		i=nb_etoiles;
		while(i>0){
			printf("*");
			i--;
		}
		
		printf("\n");
		
		nb_lignes--;
		nb_etoiles+=2;
		nb_espaces--;
	}
	return EXIT_SUCCESS;
}
