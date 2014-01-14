#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char convertir_car(char c){

	return c>'a' && c<'z' ? c-'a'+'A':c-'A'+'a';
}

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

/*Vérifie l'entrée utilisateur*/
void verifier_saisie(int * flag,char c){

	if(!isalpha(c)){
		
		*flag=1;
	}
	else{
		*flag=0;
	}
	
	return;
}

int main(){

	char saisie_utilisateur;
	int erreur_saisie=0;
	
	/*On tourne dans la boucle tant que la saisie n'est pas bonne*/
	do{
		/*Message d'erreur*/
		if(erreur_saisie){
	
			printf("Erreur dans votre saisie, veuillez seulement taper une lettre.\n\n");
		}

		/*On ne saisi qu'un caractère dans la chaîne*/	
		printf("Veuillez saisir une lettre : ");
		scanf("%c",&saisie_utilisateur);
		
		vider_buffer_stdin();
		verifier_saisie(&erreur_saisie,saisie_utilisateur);
	
	}while(erreur_saisie);
	
	printf("Voici votre caractère : %c.\n",convertir_car(saisie_utilisateur));
	
	return EXIT_SUCCESS;
}
