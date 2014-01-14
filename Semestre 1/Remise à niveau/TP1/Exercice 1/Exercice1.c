/*
 * auteur : ANTOINE FOUCAULT
 * version 0.1 : Date : Thu Sep 19 09:13:30 CEST 2013
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char tab_conv[27][5]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","---."};

void vider_buffer_stdin(){

	char c;
	while(c=getchar()!='\n'&&c!=EOF){}
}

//Fonction chargée d'enlever le retour à la ligne incorporé dans nos récupérations de chaînes par fgets
void enlever_retour(char* chaine){

	//On cherche le retour à la ligne
	char *p = strchr(chaine, '\n');

 	//S'il est trouvé on met un NULL byte à son adresse pour couper la chaîne
    	if (p)
    	{
        *p = 0;
    	}
    	//Sinon on vide le buffer qui contient encore des données
    	else{
    		vider_buffer_stdin();
    	}
}

char* coder(char* source){

	char* resultat=NULL;
	int i;

	//On vérifie la validité de la chaine passée en argument et on met les lettres en majuscule si besoin
	for(i=0;source[i];i++){

		if(!isalpha(source[i])&&!isspace(source[i])){

			printf("\nCaractère interdit dans la chaîne : %c\n", source[i]);
			return resultat;
		}
		else if(isalpha(source[i])&&islower(source[i])){

			source[i]=toupper(source[i]);
		}
	}

	//Un caractère alpha équivalant à max. 5 caractères en morse, on alloue l'espace nécessaire (5* la taille de la chaîne source + la taille de la chaine car. on ajoute un espace à chaque code morse) + le dernier caractère (---.)
	resultat=(char *) malloc(sizeof(char)*(6*strlen(source)+4));

	//On évite ainsi qu'une chaîne soit déjà interprétée
	resultat[0]='\0';
	
	//On crée la chaine en morse
	for(i=0;source[i];i++){

		//Cas particulier pour l'espace
		if(source[i]==32){
			strcat(resultat,tab_conv[26]);
			strcat(resultat," ");
		}
		else{
			strcat(resultat,tab_conv[source[i]-'A']);
			strcat(resultat," ");
		}
	}

	//On ajoute le dernier caractère
	strcat(resultat,tab_conv[26]);
	
	return resultat;
}

char* decoder(char* source){
	
	char *resultat=NULL,*check=NULL;
	char code[5]="\0",temp[2]="\0";
	int i,j,k,nb_codes=0,taille_code;

	temp[1]='\0';
	
	//On vérifie la validité de la chaine passée en argument et on compte le nombre de lettres à allouer
	if(strlen(source)<6){
		printf("\nVotre code est trop court.\n");
		return resultat;
	}

	//On vérifie la fin de la saisie
	check=source+(strlen(source)-4);
	
	if(strcmp(check,tab_conv[26])!=0){
		printf("\nVotre fin de chaîne n'est pas correcte\n");
		return resultat;
	}
	
	for(i=0,taille_code=0;source[i];i++,taille_code++){

		if(source[i]!='.'&&!isspace(source[i])&&source[i]!='-'||taille_code>=5){

			if(taille_code>=5){
				printf("\nUn code est trop long pour être interprété.\n");
				return resultat;
			}
			else{
				printf("\nCaractère interdit dans la chaîne : %c\n", source[i]);
				return resultat;
			}	
		}
		//Si on a un espace on réinitialise la taille du code et on ajoute 1 au compteur de codes
		else if(isspace(source[i])){
			taille_code=0;
			nb_codes++;
		}

	}

	//La variable nb_codes représente le nombre de lettres et espaces compris dans la chaîne de caractère
	resultat=(char *) malloc(sizeof(char)*(nb_codes));
	resultat[0]='\0';

	//On initialise nos compteurs à 0
	i=0;
	j=0;

	//strlen(source)-4 car on ne traite pas le dernier caractère (fin de saisie)
	while(i<strlen(source)-4){

		//Si on a un espace on doit traiter un code
		if(isspace(source[i])){

			//Si le code représente l'espace on traite en conséquence
			if(strcmp(code,tab_conv[26])==0){
				
				strcat(resultat," ");
			}
			//Sinon on compare le code à notre tableau de conversion
			else{			
				for(k=0;k<26;k++){

					//Si on trouve un correspondance
					if(strcmp(code,tab_conv[k])==0){

						//On passe par une variable temporaire car strcat n'accepte pas les caractères
						temp[0]=k+'A';
						strcat(resultat,temp);
					}
				}
			}

			//On réinitialise nos variables
			code[0]='\0';
			j=0;
		}
		//Sinon on ajoute le caractère de la chaîne à notre tableau de traitement
		else{
			code[j]=source[i];
			code[j+1]='\0';
			j++;
		}
		i++;
	}
	
	return resultat;
}

int main(){

	char choix=' ',saisie[200];
	char* resultat=NULL;

	//On demande à l'utilisateur s'il souhaite coder ou décoder un message
	do{

		printf("Voulez souhaitez :\n\n\t1.Coder un message\n\t2.Décoder un message\n\nChoix : ");
		scanf("%c",&choix);
		vider_buffer_stdin();
		
	}while(choix!='1'&&choix!='2');

	//On récupère l'entrée utilisateur et on la traite pour obtenir une chaine correcte
	printf("Veuillez entrer la chaine à %s (max. 200 car.): ",choix=='1'?"coder":"décoder");
	fgets(saisie,sizeof saisie,stdin);
	enlever_retour(saisie);

	//On choisit la fonction adéquat
	switch(choix){

		case '1': resultat=coder(saisie);
				break;
				
		case '2': resultat=decoder(saisie);
				break;
	}

	//Les fonctions retournent un pointeur sur NULL en cas d'erreur dans la saisie utilisateur
	if(resultat!=NULL){
		printf("\nVoici votre chaîne %s : %s",choix=='1'?"codée":"décodée",resultat);
		free(resultat);
	}
	else{
		printf("Une erreur a été détectée dans la saisie de votre chaine, veuillez entrer une chaine valide.");
	}
	
	return EXIT_SUCCESS;
}
