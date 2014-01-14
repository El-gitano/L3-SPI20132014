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
#define END_LINE 0x0 
#define SERVER_PORT 1500 
#define MAX_BUF 100 
 
int main (int argc, char *argv[]){

	int sd, newSd, cliLen, fd, n; 
	char buffer[MAX_BUF];
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
		
		printf("%s: waiting for data on port TCP %u\n",argv[0],SERVER_PORT); 
		cliLen = sizeof(cliAddr); 
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
		
		if(newSd<0){ 
			perror("cannot accept connection "); 
			return ERROR; 
		} 
		 
		if((fd = open("/tmp/fichier_serveur", O_CREAT|O_WRONLY|O_TRUNC), 0600) == -1){
			
			perror("Erreur dans la création du fichier de sauvegarde ");
			exit(1);
		}
		
		/*Réception du fichier*/
		while((n = recv(newSd, buffer, MAX_BUF, 0)) > 0){
			
			if(write(fd, &buffer, n) == -1){
			
				perror("Erreur dans l'écriture du fichier /tmp/fichier_serveur\n");
				exit(1);
			}
		}
		
		close(fd);
		
		if(n == -1){
			perror("Erreur dans la réception des données\n");
			exit(1);
		}
		else if(n == 0){
			printf("Le client s'est déconnecté, fichier uploadé dans /tmp/fichier_serveur\n");
			close(newSd);
		}
		
	} /* while (1) */ 
}
