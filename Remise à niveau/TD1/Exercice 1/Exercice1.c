#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int convertir_heure_secondes(int h,int m,int s){

	return h*3600+m*60+s;
}

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

/*Vérifie l'entrée utilisateur avec le patron demandé HH:MM:SS*/
void verifier_saisie(int * flag,char * chaine){

	if(!(isdigit(chaine[0])&&isdigit(chaine[1])&&isdigit(chaine[3])&&isdigit(chaine[4])&&isdigit(chaine[6])&&isdigit(chaine[7])&&chaine[5]==':'&&chaine[2]==':')){
		
		*flag=1;
	}
	else{
		*flag=0;
	}
	
	return;
}

int main(){

	char saisie_utilisateur[8];
	int erreur_saisie=0,heures,minutes,secondes;
	
	/*On tourne dans la boucle tant que la saisie n'est pas bonne*/
	do{
		/*Message d'erreur*/'
		if(erreur_saisie){
	
			printf("Erreur dans votre saisie, veuillez respecter le format \"HH:MM:SS\" svp.\n\n");
		}

		/*On ne saisi que 8 caractères dans la chaîne*/	
		printf("Veuillez saisir l'heure actuelle (HH:MM:SS) : ");
		scanf("%8s",saisie_utilisateur);
		
		vider_buffer_stdin();
		verifier_saisie(&erreur_saisie,saisie_utilisateur);
	
	}while(erreur_saisie);
	
	/*On récupère les données numériques une fois l'entrée utlisateur vérifiée*/
	heures=atoi(&saisie_utilisateur[0]);
	minutes=atoi(&saisie_utilisateur[3]);
	secondes=atoi(&saisie_utilisateur[6]);

	printf("Il s'est écoulé %i secondes depuis 0H00.\n",convertir_heure_secondes(heures,minutes,secondes));
	return EXIT_SUCCESS;
}
