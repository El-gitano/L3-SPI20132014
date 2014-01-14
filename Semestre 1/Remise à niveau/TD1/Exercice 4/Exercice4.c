#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

/*Vérifie l'entrée utilisateur (nombres positifs)*/
void verifier_saisie(int * flag,int x,int n){

	if(!(x>0 && n>0)){
		
		*flag=1;
	}
	else{
		*flag=0;
	}
	
	return;
}

int main(){

	int erreur_saisie=0,x,n,res;
	
	/*On tourne dans la boucle tant que la saisie n'est pas bonne*/
	do{
		/*Message d'erreur*/
		if(erreur_saisie){
	
			printf("Veuillez seulement entrer des nombres positifs.\n\n");
		}

		printf("Veuillez saisir X (positif) : ");
		scanf("%i",&x);
		vider_buffer_stdin();
		
		printf("Veuillez saisir N (positif) : ");
		scanf("%i",&n);	
		vider_buffer_stdin();
		
		verifier_saisie(&erreur_saisie,x,n);
	
	}while(erreur_saisie);
	
	res=x;
	
	for(;n>1;n--){
	
		res*=x;
	}
	
	printf("X^n=%i\n",res);
	
	return EXIT_SUCCESS;
}
