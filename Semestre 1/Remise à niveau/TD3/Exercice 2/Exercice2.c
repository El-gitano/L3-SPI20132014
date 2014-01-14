#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

typedef struct h{

	int heures;
	int min;
	int sec;
}heure;

int comparer_heure(heure *p1, heure *p2){

	int i, *a=(int *)p1, *b=(int *)p2;
	
	for(i=0;i<3 && *(a+i)==*(b+i);i++){}
	
	return *(a+i)-*(b+i);
}

void demander_heure(heure *p){

	printf("Entrer l'heure (H:M:S) : ");
	scanf("%i:%i:%i",&(p->heures),&(p->min),&(p->sec));
}

int main(){
	
	heure h1, h2, *ph1, *ph2;

	ph1=&h1;
	ph2=&h2;
	
	demander_heure(ph1);
	demander_heure(ph2);
	
	printf("Résultat de la fonction comparer_heure : %i",comparer_heure(ph1,ph2));
	
	return EXIT_SUCCESS;
}
