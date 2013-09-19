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

	printf("%i:%i:%i",p->heures,p->min,p->sec);
}


void demander_heure(heure *p){

	printf("Entrer l'heure (H:M:S) : ");
	scanf("%i:%i:%i",&(p->heures),&(p->min),&(p->sec));
}

void additionner_heure(heure * a,heure * b,heure *res){

	int i, *w=(int *)a, *x=(int *)b, *c=(int *)res;
	
	for(i=0;i<3;i++){
		*(c+i)=*(w+i)+*(x+i);
	}
}

int main(){
	
	heure h1, h2, res, *ph1, *ph2, *pres;

	ph1=&h1;
	ph2=&h2;
	pres=&res;
	
	demander_heure(ph1);
	demander_heure(ph2);
	
	additionner_heure(ph1,ph2,pres);
	
	printf("Résultat de la fonction comparer_heure est : ");
	afficher_heure_res(pres);
	
	return EXIT_SUCCESS;
}
