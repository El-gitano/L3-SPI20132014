#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

void message(int nb_j,int s){

	if(nb_j>s){
		printf("Essayez un nombre moins grand.\n");
	}
	else if(nb_j<s){
		printf("Essayez un nombre plus grand.\n");
	}
	else{
		printf("Vous avez trouvé le nombre !\n");
	}
}

int main(){

	int solution,nb_joueur=-1,nb_essais=10;
	
	/*Génération de la solution*/
	srand(time(0));
	solution=rand()%100;
	
	while(nb_joueur!=solution && nb_essais>0){
	
		printf("Entrez un nombre : ");
		scanf("%i",&nb_joueur);
		vider_buffer_stdin();
		
		if(nb_essais>1)
			message(nb_joueur,solution);
			
		nb_essais--;
	}
	
	if(nb_essais==0){
	
		printf("Vous n'avez pas trouvé le nombre dans les temps.\n");
	}
	
	return EXIT_SUCCESS;
}
