#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#ifndef sun
#include <strings.h>
#endif

#define MAXLINE 3

void do_client(int fd, int sockfd, struct sockaddr *pserv_addr, int servlen){

	int n;
	char buffer[MAXLINE];
	char data[MAXLINE];
	char chaffiche[MAXLINE+1];
	
	//On lit tout le fichier
	while((n=read(fd, data, sizeof(char)*MAXLINE-1)) != 0){
		
		data[n] = '\0';
		
		if(sendto(sockfd, data, (int)strlen(data), 0, pserv_addr, servlen) != (int)strlen(data)){
	
			perror("Erreur sendto\n");
		}
	
		n = recvfrom(sockfd, buffer, MAXLINE-1, 0, pserv_addr, &servlen);
		if(n<0){
			perror("Erreur recvfrom\n");
		}
		
		buffer[n] = '\0';		
		
		if(strcmp(data, buffer) != 0){
			
			printf("UDP client : La chaîne récupérée n'est pas égale à celle envoyée %s\n", buffer);
		}
		else{

			printf("UDP client : La chaîne récupérée est égale à celle envoyée %s\n", buffer);
		}
	}
	
	if(n == -1){
	
		perror("Erreur dans read ");
		exit(-1);
	}
}

int main(int argc, char *argv[]){

	int sockfd;
	int fd;
	struct sockaddr_in cli_addr, serv_addr;
	int portnumber;

	if(argc!=4){
	
		printf("Usage : %s [serv.addr] [port] [fichier]\n", argv[0]);
		exit(-1);
	}
	
	portnumber = atoi(argv[2]);
	if(portnumber<1){
	
		printf("Erreur dans le port\n");
		exit(-1);
	}

	if((fd = open(argv[3], O_RDONLY)) == -1){
	
		perror("Erreur dans l'ouverture du fichier de configuration\n");
		exit(-1);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(portnumber);
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	
		perror("Erreur dan la création du socket\n");
		exit(-1);
	}
	
	bzero((char *) &cli_addr, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(0);
	
	if(bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0){
	
		perror("Client : erreur dans bind\n");
		exit(-1);
	}
	
	do_client(fd, sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	
	close(fd);
	close(sockfd);
	
	return EXIT_SUCCESS;
}
