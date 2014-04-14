#include <stdio.h>
#include <stdlib.h>
#include "Alex.h"
#include "Asynth.h"

int main(){
	
	printf("\nDémarrage du programme d'analyse lexicale\n");
	
	AlexAmorcer();
	AlexReconnaitre();
	lireChaineLexicale();
	AsyntTester(0);
	
	printf("\nFin du programme d'analyse lexicale\n\n");
	return EXIT_SUCCESS;
}
