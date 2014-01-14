#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

typedef struct h{

	int heures;
	int min;
	int sec;
}heure;

typedef struct a{
	
	char ac[20];
	heure debut;
	heure fin;
}t_activite;

void afficher_heure(heure *p){

	printf("%i:%i:%i",p->heures,p->min,p->sec);
}

void demander_heure(heure *p){

	printf("Entrer l'heure (H:M:S) : ");
	scanf("%i:%i:%i",&(p->heures),&(p->min),&(p->sec));
}

void ajouter_activite(t_activite *a){
	
	printf("Heure de début : ");
	demander_heure(&(a->debut));
	printf("Heure de fin : ");
	demander_heure(&(a->fin));
	printf("Entrer activité : ");
	scanf("%20s",a->ac);
}

void afficher_activite(t_activite *a){
	
	printf("Heure de début : ");
	afficher_heure(&(a->debut));
	printf("Heure de fin : ");
	afficher_heure(&(a->fin));
	printf("Activité : %s",a->ac);
}

int main(){

	t_activite z;
	
	ajouter_activite(&z);
	afficher_activite(&z);
	
	return EXIT_SUCCESS;
}
