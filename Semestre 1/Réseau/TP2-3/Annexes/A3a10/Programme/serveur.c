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

#define SERVER_PORT 1500 
#define NB_MAX_TRANS 10
#define ERROR -1
 
int main (int argc, char *argv[]){

	int sd, newSd, cliLen, n, cpt_transfer = 0;
	int nb_t, cpt_t;
	struct sockaddr_in cliAddr, servAddr; 
	
	/*On initialise la génération des nombres aléatoire*/
	srandom(getpid());
	
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
		
		//Attente d'un nouveau client
		printf("%s: waiting for data on port TCP %u\n",argv[0],SERVER_PORT); 
		cliLen = sizeof(cliAddr); 
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
		
		if(newSd<0){ 
			perror("cannot accept connection "); 
			return ERROR; 
		} 
		
		//On initialise le compteur à 0
		cpt_transfer = 0;
		
		/*Envoi des nombres aléatoires*/
		while(cpt_transfer < NB_MAX_TRANS){
		
			nb_t = random()%50;
			printf("Envoi du nombre aléatoire %i\n", nb_t);
		
			if(send(newSd, &nb_t, sizeof(int), 0) == -1){
		
				perror("Erreur dans l'envoi des données au serveur ");
				exit(1);
			}
		
			cpt_transfer++;
		}

		close(newSd);
	} /* while (1) */ 
}
