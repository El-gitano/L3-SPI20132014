#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Topo.h"

void InitTabNiveaux(int * tab){

	int cpt;
	
	for(cpt = 0; cpt < TabNiveauxMax ; cpt++){
	
		tab[cpt] = 0;
	}
}

int noPred(int *Tab, int ind){

	return Tab[ind] == 0;
}

int noSucc(int *Tab, int ind){

	return Tab[ind] = -1;
}

int main(){

	//Initialiser (Graphe connexe avec un seul Sommet de départ nommé Tabsommets, Succ, Head, TabNbPred (initialisé), TabNiveaux, File, Niveau)
	
		int compteur, compteur2, Niveau = 0, ElementCour, ElementCour2, TailleFile;
		
		int File[TabNiveauxMax];
		int FinFile = -1;
		
		char TabSommets[TabNiveauxMax] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', ' '};
		int TabHead[TabNiveauxMax] = {0, 1, 2, 4, 5, 5, 7, 9, 9};
		int TabSucc[TabNiveauxMax*(TabNiveauxMax-1)] = {5, 4, 6, 7, 7, 1, 2, 1, 3};
		
		int TabNbPred[TabNiveauxMax] = {0, 2, 1, 1, 1, 1, 1, 2};
		
		int TabNiveaux[TabNiveauxMax];	
		InitTabNiveaux(TabNiveaux);
		
	//Trier Topo (Graphe, ElementCour, Succ, Head, TabNbPrec, File, TailleFile  => TabNiveaux)
		
		for(compteur = 0; !noPred(TabNbPred, compteur); compteur++){}//Parcourir jusqu'au sommet de départ

		assert(noPred(TabNbPred, compteur));

		Enfiler(File, &FinFile, compteur);
				
		while(!FileVide(FinFile)){//Il y a encore des noeuds à traiter donc on augmente le niveau
		
			Niveau++;

			TailleFile = FileTaille(FinFile);
			
			for(compteur2 = 0;  compteur2 < TailleFile; compteur2++){//On traite tous les noeuds du niveau actuel
				
				ElementCour = Defiler(File, &FinFile);
				TabNiveaux[ElementCour] = Niveau;
				
				//Parcourir les successeurs de ElementCour
				for(compteur = TabHead[ElementCour] ; compteur < TabHead[ElementCour + 1]; compteur ++){
					
					ElementCour2 = TabSucc[compteur];
					
					TabNbPred[ElementCour2] = TabNbPred[ElementCour2] - 1;

					if(noPred(TabNbPred, ElementCour2)){//Si plus de pred, c'est un nouveau noeud à traiter
				
						Enfiler(File, &FinFile, ElementCour2);
					}
				}
			}
		}
				
	//Afficher Résultat (TabNiveaux)
		
		for(compteur = 0; compteur < TabNiveauxMax - 1 ; compteur++){//Parcourir TabNiveaux
		
			printf("L'élément %c a le niveau : %i\n", TabSommets[compteur], TabNiveaux[compteur]);
		}
	
	return EXIT_SUCCESS;
}
