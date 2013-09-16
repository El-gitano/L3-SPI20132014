#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int calcul(int x,int n){

	if(n==0){
		return 1;
	}
	else if(x==0){
		return 0;
	}
	else{
	
		int res=x;

		for(;n>1;n--){
	
			res*=x;
		}
		
		return res;
	}
}

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

	printf("Veuillez saisir X : ");
	scanf("%i",&x);
	vider_buffer_stdin();
	
	printf("Veuillez saisir N : ");
	scanf("%i",&n);	
	vider_buffer_stdin();
	
	verifier_saisie(&erreur_saisie,x,n);
	
	if(erreur_saisie){
	
		printf("X^n n'est pas défini dans votre cas.\n");
	}
	else{
	
		printf("X^n=%i\n",calcul(x,n));
	}
	
	return EXIT_SUCCESS;
}
