#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "traitementserveur.h"

#define SUCCESS 0 
#define ERROR 1 
#define SERVER_PORT 21
#define NB_MAX_TRANS 10
 
int main (int argc, char *argv[]){

	int sd, newSd, cliLen, n, quitter = 0;
	char * cwd;
	struct sockaddr_in cliAddr, servAddr;
	REQUEST req;
	
	/*create socket */ 
	sd = socket(AF_INET, SOCK_STREAM, 0); 
	
	if(sd<0){
	
		perror("cannot open socket ");
		return ERROR; 
	}
	
	/*bind server port */ 
	servAddr.sin_family = AF_INET; 
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servAddr.sin_port = htons(SERVER_PORT); 
	
	if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr))<0){
		perror("cannot bind port "); 
		return ERROR; 
	} 
	
	listen(sd,5); 
	
	cwd = getcwd(NULL, 0);
	
	while(1){ 
		
		/*On réinitialise le dossier courrant*/
		chdir(cwd);
		
		printf("%s: waiting for data on port TCP %u\n",argv[0],SERVER_PORT); 
		cliLen = sizeof(cliAddr); 
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
		
		if(newSd<0){ 
			perror("cannot accept connection "); 
			return ERROR; 
		} 
		
		/*Traitement d'un client*/		
		printf("\n\n---Connexion d'un client---\n\n");
			
		while((n = recv(newSd, &req, sizeof(REQUEST), 0)) > 0){
		
			quitter = traiterCommande(newSd, &req);
		}

		/*Déconnexion du client*/
		if(quitter){
		
			printf("\nLe client s'est déconnecté\n\n");
		}
		else if(n == -1){
		
			perror("Erreur dans recv ");
			exit(1);
		}
	} /* while (1) */ 
}
