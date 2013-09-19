#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

typedef struct h{

	int heures;
	int min;
	int sec;
}heure;

void afficher_heure(heure *p){

	printf("Il est %i:%i:%i",p->heures,p->min,p->sec);
}

void demander_heure(heure *p){

	printf("Entrer l'heure (H:M:S) : ");
	scanf("%i:%i:%i",&(p->heures),&(p->min),&(p->sec));
}
int main(){
	
	heure h, *ph;

	ph=&h;
	
	demander_heure(ph);
	
	afficher_heure(ph);
	
	return EXIT_SUCCESS;
}
