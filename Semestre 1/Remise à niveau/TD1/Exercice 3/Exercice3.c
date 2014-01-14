#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

/*Vérifie l'entrée utilisateur avec une chaîne de caractère de 3 cases et des chiffres logiques*/
void verifier_saisie(int * flag,char * chaine){

	if(!(isdigit(chaine[0])&&isdigit(chaine[1])&&isdigit(chaine[2])&&(chaine[0]=='0' || chaine[0]=='1'))){
		
		*flag=1;
	}
	else{
		*flag=0;
	}
	
	return;
}

int main(){

	char saisie_utilisateur[3];
	int erreur_saisie=0,age;
	
	/*On tourne dans la boucle tant que la saisie n'est pas bonne*/
	do{
		/*Message d'erreur*/
		if(erreur_saisie){
	
			printf("Numéro erroné.\n\n");
		}

		/*On ne saisi que 3 caractères dans la chaîne*/	
		printf("Veuillez saisir vos 3 premiers n° de Sécurité Sociale : ");
		scanf("%3s",saisie_utilisateur);
		
		vider_buffer_stdin();
		verifier_saisie(&erreur_saisie,saisie_utilisateur);
	
	}while(erreur_saisie);
	
	age=atoi(&saisie_utilisateur[1]);
	
	printf("Bonjour %s, vous avez %i ans.\n",saisie_utilisateur[0]=='1'?"Monsieur":"Madame",age);
	
	return EXIT_SUCCESS;
}
