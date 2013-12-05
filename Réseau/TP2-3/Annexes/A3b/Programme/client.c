#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "traitementclient.h"

#define SERVER_PORT 21
#define NB_MAX_TRANS 10

int main(int argc, char *argv[]){

	int sd, rc;
	struct sockaddr_in localAddr, servAddr; 
	struct hostent *h;
	REQUEST req; 

	if(argc != 2) { 
		printf ("usage: %s <server>\n",argv[0] ) ; 
		exit(1) ; 
	}
	
	/*On récupère l'adresse IP du système distant*/
	h = gethostbyname(argv[1]);
	
	if(h==NULL){ 
		printf("%s: unknown host '%s'\n",argv[0],argv[1]); 
		exit(1); 
	}
	 
	servAddr.sin_family = h->h_addrtype; 
	memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	servAddr.sin_port = htons(SERVER_PORT); 
	
	/*create socket */ 
	sd = socket(AF_INET, SOCK_STREAM, 0); 
	
	if(sd<0){ 
		perror("cannot open socket "); 
		exit(1); 
	} 
	
	/* bind any port number */ 
	localAddr.sin_family = AF_INET; 
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	localAddr.sin_port = htons(0); 
	
	rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
	
	if(rc<0){
		printf("%s: cannot bind port TCP %u\n",argv[0],SERVER_PORT); 
		perror("error "); 
		exit(1); 
	}
	
	/*connect to server */ 
	rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)); 
	
	if(rc<0){ 
		perror ("cannot connect "); 
		exit(1) ; 
	}

	printf("Connecté au serveur %s\n\n", argv[1]);
	
	while(1){
	
		recupererCommande(&req);
		traiterCommande(sd, &req);
	}

	return 0;
}
