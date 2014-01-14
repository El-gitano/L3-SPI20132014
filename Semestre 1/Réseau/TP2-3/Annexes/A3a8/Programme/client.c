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

#define SERVER_PORT 1500 
#define MAX_BUF 100 

int main(int argc, char *argv[]){

	int sd, rc, i, fd;
	char buffer[MAX_BUF];
	struct sockaddr_in localAddr, servAddr; 
	struct hostent *h; 

	if(argc != 3) { 
		printf ("usage: %s <server> <file_to_transfer>\n",argv[0] ) ; 
		exit(1) ; 
	}

	/*On ouvre le fichier*/
	if((fd = open(argv[2], O_RDONLY)) == -1){
		
		perror("Erreur dans l'ouverture du fichier ");
		exit(1);
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
		perror ( "cannot connect "); 
		exit(1) ; 
	}
	
	//memset(buffer, 0x0, sizeof(buffer));
	
	/*Envoi du fichier*/
	while((i = read(fd, &buffer, sizeof(char)*MAX_BUF)) != 0 && i != -1){
		
		buffer[i] = '\0';
		
		if(send(sd, &buffer, strlen(buffer), 0) == -1){
		
			perror("Erreur dans l'envoi des données au serveur ");
			exit(1);
		}
		
		//memset(buffer, 0x0, sizeof(buffer));
	}
	
	if(i == -1){
		perror("Erreur dans la lecture du fichier ");
		exit(-1);
	}
	
	printf("Fichier %s envoyé\n", argv[2]);
	
	close(sd);
	close(fd);
	
	return 0;
}
