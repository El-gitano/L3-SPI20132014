#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "message.h"

#define TAILLE_TABLE 30

/*Prototypes*/
void reinitialiser_table(REQUEST *, int *);
void quitter(int, REQUEST *);
int lancer_sauvegarde(int, int *, int *, REQUEST *);
int verifier_presence(REQUEST, REQUEST *);

//Réinitialise une table
void reinitialiser_table(REQUEST *table, int *indice){

	int i;
	
	for(i=0; i<TAILLE_TABLE; i++){
	
		table[i].numEnvoi = -1;
	}
	
	*indice = 0;
}

//Sauvegarde de la table actuelle et fermeture de la connexion avec un client
void quitter(int numClient, REQUEST *table){

	int fd, i;
	char fichier[100];
	
	//On change de dossier
	if(chdir("Mesures") == -1){
	
		perror("Erreur dans le changement de dossier ");
		exit(-20);
	}
	
	//On ouvre le fichier
	sprintf(fichier, "Mesures_client%d", numClient);
	
	if((fd = open(fichier, O_WRONLY|O_CREAT|O_EXCL, 0600)) == -1){
	
		perror("Erreur dans l'ouverture du fichier de sauvegarde ");
		
		exit(-20);
	}
	
	//On enregistre les informations
	for(i=0; table[i].numEnvoi != -1 ; i++){
	
		if(write(fd, &(table[i]), sizeof(REQUEST)) == -1){
		
			perror("Erreur dans l'écriture de la structure REQUEST dans le fichier ");			
			exit(-20);
		}
	}
	
	//On ferme le fichier
	close(fd);
	free(table);
	
	exit(0);
}

int lancer_sauvegarde(int numClient, int *numFichier, int *indTable, REQUEST *table){

	int fd, i;
	char fichier[100];
	
	//On change de dossier
	if(chdir("Mesures") == -1){
	
		perror("Erreur dans le changement de dossier ");
		return 0;
	}
	
	//On ouvre le fichier
	sprintf(fichier, "Mesures_client%d_%d", numClient, *numFichier);
	
	if((fd = open(fichier, O_WRONLY|O_CREAT|O_EXCL, 0600)) == -1){
	
		perror("Erreur dans l'ouverture du fichier de sauvegarde ");
		
		if(chdir("..") == -1){

			perror("Erreur dans le changement de dossier ");
			return 0;
		}
		
		return 0;
	}
	
	//On enregistre les informations
	for(i=0; i<TAILLE_TABLE/*-1*/; i++){
	
		if(write(fd, &(table[i]), sizeof(REQUEST)) == -1){
		
			perror("Erreur dans l'écriture de la structure REQUEST dans le fichier ");
			
			if(chdir("..") == -1){
	
				perror("Erreur dans le changement de dossier ");
				return 0;
			}
			close(fd);
			return 0;
		}
	}
	
	//On ferme le fichier et on revient au dossier parent
	close(fd);
	
	if(chdir("..") == -1){
	
		perror("Erreur dans le changement de dossier ");
		return 0;
	}
	
	//On réinitialise la table et on incrémente le compteur de fichiers
	*numFichier += 1;
	reinitialiser_table(table, indTable);
	
	return 1;
}

int verifier_presence(REQUEST x, REQUEST *table){

	int i;
	
	for(i=0; i<TAILLE_TABLE; i++){
	
		if(table[i].numEnvoi == x.numEnvoi){
		
			return 1;
		}
	}
	
	return 0;
}

int main(int argc, char *argv[]){

	//Pointeur sur notre future table de réception et variables attachées
	REQUEST *table;
	int indTable;
	
	//Variables nécessaires aux communications réseau
	int sd, sdClient;
	struct sockaddr_in localAddr, cliAddr;
	int port;
	RESPONSE rep;
	REQUEST reqTemp;
	
	//Itérateur et compteurs
	int n, numClient = 0, numFichier = 0;
	
	//Vérification et récupération des arguments
	if(argc != 2){
	
		printf("Usage : %s [port]\n", argv[0]);
		exit(0);
	}
	
	port = atoi(argv[1]);
	
	//Création de la table de réception des requêtes
	printf("Création de la table de réception des requêtes\n");
	
	if((table = (REQUEST *)malloc(sizeof(REQUEST)*TAILLE_TABLE)) == NULL){
	
		perror("Erreur dans l'allocation de la zone mémoire de réception ");
		exit(-1);
	}
	
	printf("Table crée\n\n");
	
	//Création du dossier Mesures
	printf("Tentative de création du dossier \"Mesures\"\n");
	if(mkdir("Mesures", 0777) == -1){
	
		printf("Dossier \"Mesure\" déjà crée\n\n");
	}
	else{
	
		printf("Dossier \"Mesures\" crée\n\n");
	}
	
	//Création du socket
	printf("Création du socket\n");
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	
		perror("Erreur dans la création du socket ");
		exit(-2);
	}
	
	printf("Socket crée\n\n");
	
	//Remplissage des informations locales
	printf("Association du socket au port %i\n", port);
	
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(port);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr)) == -1){
		
		perror("Impossible d'assigner le socket au port définit ");
		exit(-3);
	}
	
	printf("Association effectuée avec succès\n\n");
	
	printf("En attente de client...\n\n");
	
	if(listen(sd, 5) == -1){
	
		perror("Erreur dans la mise en écoute ");
		exit(-4);
	}
	
	while(1){
		
		socklen_t tailleAddr = sizeof(cliAddr);
		if((sdClient = accept(sd, (struct sockaddr *) &cliAddr, &tailleAddr)) == -1){
		
			perror("Erreur dans l'établissement d'une nouvelle connexion avec un client ");
			exit(-5);
		}
		
		//Nouveau processus pour chaque client
		switch(fork()){
		
			case -1:	perror("Erreur dans la création du processus fils pour le nouveau client ");
						exit(-6);
						break;
					
			case 0:		reinitialiser_table(table, &indTable);
						
						//On lance la réception des informations
						while(1){
						
							if((n = recv(sdClient, &reqTemp, sizeof(REQUEST), 0)) <= 0){
							
								if(n == 0){
								
									printf("FILS : Le client s'est déconnecté\n");
									
									//Création du fils de traitement
									switch(fork()){
									
										case -1:	perror("Erreur dans la création du processus de sauvegarde à la déconnexion ");
													exit(-39);
										
										case 0:		quitter(numClient, table);
													break;
									}
									
									exit(0);
								}
								else if(n == -1){
								
									perror("FILS : Erreur dans la réception des données ");
									exit(-1);
								}
							}
							
							printf("Réception de données\n");
							
							//On vérifie que le client n'a pas envoyé une requête de déconnexion
							if(reqTemp.numEnvoi == -1){
								
								//Création du fils de traitement
								switch(fork()){
								
									case -1:	perror("Erreur dans la création du processus de sauvegarde à la déconnexion ");
												exit(-39);
									
									case 0:		quitter(numClient, table);
												exit(0);
												break;
								}
								
								exit(0);
							}
							
							//On vérifie que la requête n'est pas déjà située dans la table
							if(!verifier_presence(reqTemp, table)){
								
								if(reqTemp.temperature > 0 && reqTemp.pression > 0){
									
									//On ajoute la requête à la table
									memcpy(&(table[indTable]), &reqTemp, sizeof(reqTemp));
									indTable ++;
									
									//On met le code de réponse à OK
									rep.code = 200;
								}
								else{
								
									//On met le code de réponse à ERREUR
									rep.code = 500;
								}
								
								//On envoi la réponse
								rep.ret_numEnvoi = reqTemp.numEnvoi;
								
								if(send(sdClient, &rep, sizeof(RESPONSE), 0) == -1){
								
									perror("FILS : Erreur dans l'envoi de la réponse au client ");
									exit(-2);
								}
								
								//On agit en conséquence si la table est pleine
								if(indTable == TAILLE_TABLE-1){
									
									//Création du fils de traitement
									switch(fork()){
									
										case -1:	perror("Erreur dans la création du fils chargé de la sauveagarde ");
													exit(-3);
													
										case 0:
													if(lancer_sauvegarde(numClient, &numFichier, &indTable, table)){
									
														printf("Sauvegarde de la table dans le fichier Mesures_client%i_%i.txt\n", numClient, numFichier-1);
													}
													else{
										
														printf("FILS de sauvegarde de %i : Erreur dans la sauvegarde de la table\n", numClient);
														perror("");
														exit(-1);
													}
													
													break;
									}
								}
							}
						}
						
						break;
		}
		
		printf("Nouveau client lancé\n\n");
		numClient++;
	}
}
