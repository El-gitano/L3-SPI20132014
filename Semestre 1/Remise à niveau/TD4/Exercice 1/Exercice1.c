#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define MAX 10

typedef struct noeud *ptrNoeud;

typedef struct noeud{

	int valeur;
	ptrNoeud suivant;
}Noeud;

typedef ptrNoeud Liste;

void afficher(Liste l){

	int i=0;
	
	printf("\n");
	
	if(l){
	
		do{
		
			printf("Elém %d : %d\n",++i,l->valeur);
			l=l->suivant;
		}while(l);
	}
	else
		printf("La liste est vide");
}

int estVide(Liste l) {

	return (l==NULL);
}

int valeur(Liste l){ 

	return (l->valeur);
}

void supprimerPrem(Liste *l){
	
	ptrNoeud aSupr=*l;
	*l=(*l)->suivant;
	
	printf("Je détruis : %d \n",aSupr->valeur);
	
	free(aSupr);
}

void LajouterEnTete(int v, Liste *l){

	ptrNoeud nouv, temp;
	
	if(nouv=(ptrNoeud)malloc(sizeof(Noeud))){
	
		nouv->valeur = v;
		nouv->suivant = NULL;
		
		if(estVide(*l)){
		
			*l = nouv;
		}
		else{
		
			temp = *l;
			*l = nouv;
			nouv->suivant = temp;
		}
	}
	else{
	
		printf("Problème d'allocation mémoire.\n");
		exit(1);
	}
}

int Llongueur(Liste l){

	int i;
	
	if(!estVide(l)){
	
		for( i=1 ; l->suivant!=NULL ; l=l->suivant, i++){}
	}
	
	return i;
}

//On appelle cette fonction avec une longueur de 0
int LlongueurR(Liste l, int longueur){

	if(l==NULL){
		
		return longueur;
	}
	else{
	
		LlongueurR(l->suivant, longueur+1);
	}
}

//La fonction retourne l'adresse de la première occurence de val ou NULL si elle ne trouve pas la valeur
ptrNoeud Lrecherche(Liste l, int val){

	if(!(estVide(l))){
	
		for(; l!=NULL && valeur(l)!=val ; l=l->suivant){}
		return l;
	}
}

//On appelle la fonction en passant la valeur NULL à res
ptrNoeud LrechercheR(Liste l, int val, ptrNoeud res){

	//Si on arrive en fin de liste ou  qu'on a trouvé notre valeur
	if(l==NULL || res!=NULL){
	
		return res;
	}
	else if(valeur(l) == val){
	
		LrechercheR(l->suivant, val, l);
	}
	else{
	
		LrechercheR(l->suivant, val, res);
	}
}

//Concatène une liste à la suite d'une autre (si les deux listes ne sont pas vides)
int append(Liste l1, Liste l2){

	if(!estVide(l1) && !estVide(l2)){
	
		ptrNoeud fin_l1;
	
		//On se positionne au dernier élément de l1
		for(fin_l1=l1 ; fin_l1->suivant!=NULL ; fin_l1=fin_l1->suivant){}
	
		fin_l1->suivant = l2;
		return 1;
	}
	else{
		return 0;
	}
}

//Insère la liste l2 au rang n de la liste l1
int nconc(Liste l1, Liste l2, int n){

	ptrNoeud pl1, fin_l2;
	int i;
	
	if(estVide(l1)||estVide(l2)){
		return 0;
	}
	
	//On se positionne à l'élément n de la liste l1
	for(pl1=l1, i=0 ; pl1 && i<n ; pl1=pl1->suivant, i++){}
	
	//On se positionne à la fin de la liste l2
	for(fin_l2=l2 ; fin_l2->suivant!=NULL ; fin_l2=fin_l2->suivant){}
	
	//Si l'indice n est plus grand que la longueur de l1 (la comparaison est faite ici pour des raisons d'optimisations
	if(pl1){
		
		fin_l2->suivant = pl1->suivant;
		pl1->suivant = l2;
		return 1;
	}
	else{

		return 0;
	}
	
}

int Lsupprime(Liste * l,int n){

	ptrNoeud n_prec,n_cour;
	int i;//i représente le nombre d'opérations afin de savoir si on doit chaîner des éléments précédents à celui supprimé
	
	if(estVide(*l)){
		
		return 0;
	}
	
	n_cour=*l;

	//On se place à l'élément de valeur n s'il est dans la liste
	for(i=0 ; valeur(n_cour)!=n && n_cour!=NULL; n_cour=n_cour->suivant, i++){}
	
	//Si on a trouvé l'élément
	if(n_cour){
	
		//Si on ne se situe pas en début de liste
		if(i>0){
			
			//On place n_prec à l'élément précédent celui à supprimer
			for(n_prec=*l ; i>1 ; i--, n_prec=n_prec->suivant){}
			
			n_prec->suivant = n_cour->suivant;
		}
		//On se situe en début de liste
		else{
		
			*l=n_cour->suivant;
		}
		
		free(n_cour);
		return 1;
	}
	else{
		
		printf("Pas d'élément de valeur %i à supprimer.\n", n);
		return 0;
	}
}

//On initialise prec à NULL
int LsupprimeR(Liste *l, int n, ptrNoeud prec){
	
	//On ne trouve pas l'élément à supprimer			
	if(!(*l)){
		return 0;
	}
	//On a trouvé la valeur à supprimer
	else if(valeur(*l)==n){
	
		//On ne se situe pas en début de liste
		if(prec!=NULL){
			
			printf("Adresse de prec %i : %p\n", valeur(prec), prec);
			printf("Adresse de l %i : %p\n", valeur(*l), (*l));
			printf("Adresse de suivant %i : %p\n", valeur((*l)->suivant), (*l)->suivant);
			prec->suivant = (*l)->suivant;
			printf("Adresse pointée par %i %i : %p\n", valeur(prec), valeur(prec->suivant), prec->suivant);	
			free(*l);	
			printf("Adresse de %i : %p\n", valeur(prec), prec);
			printf("Adresse pointée par %i %i : %p\n", valeur(prec), valeur(prec->suivant), prec->suivant);		
		}
		//On se situe en début de liste (OK)
		else{
		
			ptrNoeud temp = *l;
			*l = (*l)->suivant;
			free(temp);
		}
		
		return 1;
	}
	//On parcourt la liste
	else{
		LsupprimeR(&((*l)->suivant), n, *l);
	}
}

Liste listeCreer(){ 
	return NULL;
}

void ajouterFin(int v, Liste *l){ 

	/* création d'un nouveau noeud */
	/* ajout en fin de liste */ 
	ptrNoeud nouv, courant;
	
	if (nouv=(ptrNoeud)malloc(sizeof(Noeud))){ 
	
		nouv->valeur=v;
		nouv->suivant=NULL;
		
		/* Premier cas L est vide */
		
		if(!*l)
			*l=nouv; 
		else{
		
			courant=*l;
			
			while(courant->suivant)
				courant=courant->suivant;
				
			courant->suivant=nouv;
		}
	}
	else{
		
		printf("Erreur d'allocation");
		exit(1);
	}
}

int main(){

	Liste l1, l2, l3; 
	int i; 
	ptrNoeud a=NULL,b=NULL;
	
	l1=listeCreer();
	l2=listeCreer();
	l3=listeCreer();
	
	for(i=0;i<MAX; i++)
		ajouterFin(i,&l1);
	
	for(i=MAX;i!=0;i--){
		ajouterFin(i,&l2);
	}
	
	for(i=20;i<30; i++)
		ajouterFin(i,&l3);

	afficher(l1);
	afficher(l2);

	printf("\nLa longueur de la liste l1 est %i ou %i", Llongueur(l1),LlongueurR(l1,0));
	
	printf("\n\nAjout de 21 en tête\n");
	
	LajouterEnTete(21,&l1);
	
	afficher(l1);
	
	printf("\nConcaténation de l1 et l2\n");
	
	append(l1, l2);
	
	afficher(l1);
	
	printf("\nConcaténation de l1 et l3 en position 7\n");
	
	nconc(l1, l3, 7);
	
	afficher(l1);
	
	printf("\nSupression de 21 et 27\n");

	Lsupprime(&l1, 21);
	LsupprimeR(&l1, 3, NULL);
	
	afficher(l1);
	
	a=Lrecherche(l1,7);
	b=LrechercheR(l1, 7, b);
	
	printf("\nL'élément contenant la valeur 7 est à l'adresse mémoire %p ou %p\n\n", a, b);
	
	int x = 0;
	
	while(!estVide(l1)){  
		 
		printf("%d, ",x++);
		supprimerPrem(&l1);
	}

	afficher(l1);
	
	printf("\n");
	
	return EXIT_SUCCESS;
}
