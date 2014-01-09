#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include "message.h"

//Variables d'échange des données
REQUEST req;
RESPONSE rep;

//Tubes des fils
int tubeF1[2], tubeF2[2];

//Pid des fils
pid_t pidF1, pidF2;

//Descripteur du socket TCP lié avec le serveur
int sd, accuse = 1;

void int_handler(int sig){

	//Envoi du message de déconnexion au serveur
	printf("Envoi de la requête de déconnexion au serveur\n");
	
	req.numEnvoi = -1;
	
	if(send(sd, &req, sizeof(req), 0) == -1){
		
		perror("Erreur dans l'envoi des données au serveur ");
		exit(-15);
	}	
	
	//On tue les deux fils
	kill(SIGQUIT, pidF1);
	kill(SIGQUIT, pidF2);
	
	//On ferme les tubes
	close(tubeF1[0]);
	close(tubeF2[0]);
	
	printf("Fin du programme client\n");
	
	exit(0);
}

//Réaction du programme à un timeout
void alrm_handler(int sig){

	printf("Timeout dépassé, renvoi de la requête\n");
	
	if(send(sd, &req, sizeof(req), 0) == -1){
		
		perror("Erreur dans l'envoi des données au serveur ");
		exit(-12);
	}
	
	accuse = 0;
}
	
int main(int argc, char *argv[]){
	
	//Variables nécessaires pour la connexion au serveur
	struct sockaddr_in serveurAddr, localAddr;
	struct hostent *infoServ;
	int port;
	
	//Itérateurs
	int nbEnvoi = 0, i;
	
	//Variable pour la redirection de signal
	struct sigaction s_action;
	
	//On vérifie le nombre d'arguments
	if(argc != 3){
	
		printf("Usage : %s [nom_serveur] [port]\n", argv[0]);
		exit(-1);
	}
	
	//Variables pour les fils
	float temperature, pression;
	
	//On récupère les arguments
	port = atoi(argv[2]);
	
	//On essai de récupérer des informations sur le serveur à partir du nom de domaine
	printf("Récupération des informations sur le serveur\n");
	
	if((infoServ = gethostbyname(argv[1])) == NULL){
	
		perror("Serveur inexistant/inconnu ");
		exit(-2);
	}
	
	printf("Informations récupérées\n\n");
	
	//On rempli la structure du serveur
	serveurAddr.sin_family = infoServ->h_addrtype;
	memcpy((char *) &serveurAddr.sin_addr.s_addr, infoServ->h_addr_list[0], infoServ->h_length);
	serveurAddr.sin_port = htons(port);
	
	//On crée le socket
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	
		perror("Erreur dans la création du socket ");
		exit(-3);
	}
	
	//On remplit la stucture du client
	localAddr.sin_family = AF_INET; 
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	localAddr.sin_port = htons(0); 
	
	//On associe notre socket à un port aléatoire
	if(bind(sd, (struct sockaddr *)&localAddr, sizeof(localAddr)) == -1){
	
		perror("Erreur dans l'association du socket à un port ");
		exit(-4);
	}
	
	//On se connecte au serveur	
	printf("Tentative de connexion au serveur\n");
	
	if(connect(sd, (struct sockaddr *) &serveurAddr, sizeof(serveurAddr)) == -1){
	
		perror("Impossible de se connecter au serveur ");
		exit(-5);
	}
	
	printf("Connexion réussie\n\n");
	
	//On lance les fils
	printf("Démarrage des processus fils\n");
	
	//On crée le tube du fils 1
	if(pipe(tubeF1) == -1){
	
		perror("Erreur dans la création du tube du fils 1 ");
		exit(-6);
	}
	
	//On lance le fils 1
	switch(pidF1 = fork()){
	
		case -1:	perror("Erreur dans la création du fils 1 ");
					exit(-7);
					break;
				
		case 0:		//Fils 1
		
				//Fermuture de l'entrée en lecture du tube
				close(tubeF1[0]);
				
				//On initialise la génération de nombre aléatoire
				srand(getpid());
				
				//On envoi des données aléatoires toutes les 20s
				while(1){
				
					sleep(20);
					temperature = rand()%100/2.0;
					
					if(write(tubeF1[1], &temperature, sizeof(float)) == -1){
					
						perror("FILS 1 : Erreur dans l'écriture dans le tube ");
						exit(0);
					}
				}
				
				break;
	}
	
	//Fermeture de l'entrée en écriture de tubeF1
	close(tubeF1[1]);
	
	//On crée le tube du fils 2
	if(pipe(tubeF2) == -1){
	
		perror("Erreur dans la création du tube du fils 2 ");
		exit(-8);
	}
	
	//On lance le fils 2
	switch(pidF2 = fork()){
	
		case -1:	perror("Erreur dans la création du fils 2 ");
					exit(-9);
					break;
				
		case 0:		//Fils 2
		
				//Fermuture de l'entrée en lecture du tubeF1 et tubeF2 et écriture de tubeF1
				close(tubeF1[0]);
				close(tubeF1[1]);
				close(tubeF2[0]);
				
				//On initialise la génération de nombre aléatoire
				srand(getpid());
				
				//On envoi des données aléatoires toutes les 20s
				while(1){
				
					sleep(20);
					pression = rand()%400/2.0;
					
					if(write(tubeF2[1], &pression, sizeof(float)) == -1){
					
						perror("FILS 2 : Erreur dans l'écriture dans le tube ");
						exit(0);
					}
				}
				
				break;
	}
	
	//Fermeture de l'entrée en écriture de tubeF2
	close(tubeF2[1]);
	
	printf("Processus fils démarrés\n\n");
	
	//On redirige les signaux SIGINT et SIGALARM
	signal(SIGINT, int_handler);
	
	s_action.sa_handler = alrm_handler;
	
	if(sigaction(SIGALRM, &s_action, NULL) == -1){
	
		perror("Erreur dans la redirection du signal SIGALRM ");
		exit(-16);
	}
	
	//Démarrage de l'envoi des informations au serveur
	printf("Démarrage de l'envoi des informations au serveur\n\n");
	
	while(1){
	
		//On récupère les informations des capteurs
		if(read(tubeF1[0], &temperature, sizeof(float)) == -1){
		
			perror("Erreur dans la lecture des informations du fils 1 à travers le tube ");
			exit(-10);
		}
		
		if(read(tubeF2[0], &pression, sizeof(float)) == -1){
		
			perror("Erreur dans la lecture des informations du fils 2 à travers le tube ");
			exit(-11);
		}
		
		//On envoi les informations au serveur
		req.temperature = temperature;
		req.pression = pression;
		req.numEnvoi = nbEnvoi;
		
		if(send(sd, &req, sizeof(req), 0) == -1){
		
			perror("Erreur dans l'envoi des données au serveur ");
			exit(-12);
		}
		
		printf("Données envoyées, en attente de la réception de l'accusé %i (%f : %f)\n", req.numEnvoi, req.temperature, req.pression);
		
		//On attend l'accusé de réception pendant 10 secondes		
		alarm(10);
		
		if((i = recv(sd, &rep, sizeof(rep), 0)) < 0){
		
			if(i == 0){
			
				printf("Le serveur s'est déconnecté, fermeture du client\n");
				exit(-13);
			}
			else if(i == -1){
			
				perror("Erreur dans la réception de l'accusé du serveur ");
				exit(-14);
			}
		}

		//En cas de réponse du serveur on désactive le timeout et on affiche l'état de la réception		
		if(accuse == 1){
		
			alarm(0);		
			printf("Reception de l'accusé n°%i, code %i -> %s\n", rep.ret_numEnvoi, rep.code, rep.code == 200 ? "OK":"ERREUR");
		}
		
		//On incrémente le n° d'envoi
		nbEnvoi++;
		accuse = 1;
	}
}
