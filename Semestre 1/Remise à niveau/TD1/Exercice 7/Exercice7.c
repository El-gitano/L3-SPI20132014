#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void vider_buffer_stdin(){

	int c;
	while ((c=getchar()) != '\n' && c != EOF);
}

float moyenne(int notes[],int n){

	float res=0;
	int i;
	
	for(i=0;i<n;i++){
	
		res=res+notes[i];
	}
	
	return res/n;
}

int nbrecus(int notes[],int n){

	int nbrecus=0,i;
	
	for(i=0;i<n;i++){
	
		if(notes[i]>=10){
			nbrecus++;
		}
	}
	
	return nbrecus;
}

float prc_recus(int notes[],int n){

	float nbrecus=0;
	int i;
	
	for(i=0;i<n;i++){
	
		if(notes[i]>=10){
			nbrecus++;
		}
	}
	
	return nbrecus/n*100;
}

int max(int notes[],int n){

	int max=0,i;
	
	for(i=0;i<n;i++){
	
		if(notes[i]>max){
			max=notes[i];
		}
	}
	
	return max;
}

int min(int notes[],int n){

	int min=20,i;
	
	for(i=0;i<n;i++){
	
		if(notes[i]<min){
			min=notes[i];
		}
	}
	
	return min;
}

int main(){

	int nb_etudiants=0,i;
	int * notes;
	
	do{
		printf("Entrez le nombre d'étudiants : ");
		scanf("%i",&nb_etudiants);
		vider_buffer_stdin();
		
	}while(nb_etudiants<=0);
	
	notes=malloc(sizeof(int)*nb_etudiants);
	
	for(i=0;i<nb_etudiants;i++){
	
		do{
			printf("Saisissez la note du %i%s étudiant : ",i+1,i+1==1?"er":"ème");
			scanf("%i",&notes[i]);
			vider_buffer_stdin();
			
		}while(notes[i]<0 || notes[i]>20);
	}
	
	printf("\nMoyenne : %f\n",moyenne(notes,nb_etudiants));
	printf("Meilleure note : %i\n",max(notes,nb_etudiants));
	printf("Plus mauvais note : %i\n",min(notes,nb_etudiants));
	printf("Nombre de reçus : %i\n",nbrecus(notes,nb_etudiants));
	printf("Pourcentage de reçus : %f%\n",prc_recus(notes,nb_etudiants));
	
	free(notes);
	
	return EXIT_SUCCESS;
}
