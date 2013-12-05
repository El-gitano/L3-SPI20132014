#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#ifndef sun
#include <strings.h>
#endif

#define MAXLINE 4

void do_server(int sockfd, struct sockaddr *pcli_addr, int maxclilen){

	int fd, n;

	char messg[MAXLINE];
	char chaffiche[MAXLINE+1];
	
	while(1){

		if((fd = open("fichier_save", O_CREAT|O_WRONLY, 0666)) == -1){
	
			perror("Erreur dans l'ouverture du fichier de sauvegarde\n");
			exit(-1);
		}
		
		lseek(fd, 0, SEEK_END);
		
		n = recvfrom(sockfd, messg, MAXLINE*sizeof(char), 0, pcli_addr, &maxclilen);

		if(n<0){
		
			perror("Erreur dans recv\n");
		}
		
		messg[n] = '\0';
		strcpy(chaffiche, messg);
		chaffiche[n] = '\0';
		
		printf("UDP server : %s\n", chaffiche);
	
		if(write(fd, messg, n) == -1){
		
			perror("Erreur dans write.\n");
		}

		if(sendto(sockfd, messg, n, 0, pcli_addr, maxclilen)!=n){
			
			perror("Erreur sendto\n");
		}
		
		close(fd);
	}
}

int main(int argc, char *argv[]){
	
	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
	int portnumber;
	int fd;
	
	if(argc!=2){

		printf("Usage : %s [port]\n", argv[0]);
		exit(-1);
	}
	portnumber = atoi(argv[1]);
	if(portnumber<1){
	
		printf("Erreur dans le paramètre port\n");
		exit(-1);
	}
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	
		perror("Impossible de créer le socket\n");
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(portnumber);
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
	
		perror("Erreur dans bind\n");
	}
	
	do_server(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	
	close(sockfd);
	
	return(EXIT_SUCCESS);
}
