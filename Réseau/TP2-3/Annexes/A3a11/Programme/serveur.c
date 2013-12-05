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

#define SUCCESS 0 
#define ERROR 1 
#define SERVER_PORT 1500 
#define NB_MAX_TRANS 10
 
int main (int argc, char *argv[]){

	int sd, newSd, cliLen, n;
	int nb_t;
	struct sockaddr_in cliAddr, servAddr;
	
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
	
	while(1){ 
		
		//Attente du client
		printf("%s: waiting for data on port TCP %u\n",argv[0],SERVER_PORT); 
		cliLen = sizeof(cliAddr); 
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
		
		if(newSd<0){ 
			perror("cannot accept connection "); 
			return ERROR; 
		} 
		
		/*Réponse au client*/		
		if(recv(newSd, &nb_t, sizeof(int), 0) == -1){
		
			perror("Erreur dans la réception de la requête cliente\n");
			exit(1);
		}
		
		printf("Réception d'une requête\n");
		
		//Envoi direct de la réponse
		if(send(newSd, &nb_t, sizeof(int), 0) == -1){
		
			perror("Erreur dans l'envoi de la réponse au client\n");
			exit(1);
		}
		
		printf("Réponse envoyée\n");
		close(newSd);	
	} /* while (1) */ 
}
