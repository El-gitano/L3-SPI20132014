#include "traitementserveur.h"

int traiterCommande(int socket, REQUEST *r){
	
	if(strcmp(r->commande, "ls") == 0){
	
		ls(socket);
	}
	else if(strcmp(r->commande, "cd") == 0){
	
		cd(socket, r->fichier);
	}
	else if(strcmp(r->commande, "get") == 0){
	
		get(socket, r->fichier);
	}
	else if(strcmp(r->commande, "put") == 0){
	
		put(socket, r->fichier, r->taille);
	}
	else if(strcmp(r->commande, "exit") == 0){
	
		quitter(socket);
		return 1;
	}
	else{
		
		printf("Une requête incorrecte a été détectée\n");
		message_erreur(socket, "Requête incorrecte");
	}
	
	return 0;
}

void ls(int sock){

	DIR *d;
	struct dirent *entree;
	RESPONSE *r;
	int cpt_fichiers = 0;
	
	printf("Appel de la fonction ls\n");
	
	/*Allocation de la structure RESPONSE*/
	if((r = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
		
		perror("Erreur dans l'allocation de la structure de réponse ");
		message_erreur(sock, "SERVEUR - Erreur système dans la commande ls\n");
		exit(1);
	}
	
	/*Ouverture du dossier actuel*/
	if((d = opendir(".")) == NULL){
	
		perror("Erreur dans l'ouverture du dossier actuel ");
		message_erreur(sock, "SERVEUR - Erreur dans la commande ls (impossible d'ouvrir le dossier)\n");
		return;
	}
	
	/*On compte le nombre de fichiers*/
	while((entree = readdir(d)) != NULL){
		
		cpt_fichiers++;
	}
	
	/*Envoi de la réponse OK au client*/
	r->code = 200;
	
	if(send(sock, r, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans l'envoi d'une reponse erreur ");
		exit(1);
	}
	
	/*On envoi le nombre de fichiers au client*/
	if(send(sock, &cpt_fichiers, sizeof(int), 0) == -1){
	
		perror("LS - Erreur dans l'envoi du nombre de fichiers ");
		exit(1);
	}
	
	rewinddir(d);
	
	/*On envoi les fichiers*/
	while((entree = readdir(d)) != NULL){
	
		/*Envoi de la taille du fichier actuel*/
		if(send(sock, &(entree->d_reclen), sizeof(unsigned short), 0) == -1){
		
			perror("LS - Erreur dans l'envoi de la taille du fichier ");
			exit(1);
		}
		
		/*Envoi du nom du fichier actuel*/
		if(send(sock, entree->d_name, entree->d_reclen, 0) == -1){
		
			perror("LS - Erreur dans l'envoi de la taille du fichier ");
			exit(1);
		}
	}
	
	/*Nettoyage*/
	closedir(d);
	free(r);
	
	printf("Fonction ls OK\n");
}

void cd(int sock, char *f){

	RESPONSE *r;
	char *messageok = "SERVEUR - Dossier courant changé\n";
	
	/*Allocation de la structure RESPONSE*/
	if((r = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
		
		perror("Erreur dans l'allocation de la structure de réponse ");
		exit(1);
	}
	
	printf("\nTentative de changement de dossier pour %s\n", f);
	
	if(chdir(f) == -1){
	
		perror("Erreur dans le changement d'un dossier ");
		message_erreur(sock, "SERVEUR - Impossible de changer le dossier courant");
		printf("Retour");
		return;
	}
	
	printf("Dossier courant changé, nouveau dossier courant : %s\n\n", getcwd(NULL, 0));
	
	/*Envoi de la réponse au client*/
	r->code = 200;
	r->taille = strlen(messageok)+1;
	
	if(send(sock, r, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans l'envoi d'une reponse erreur ");
		exit(1);
	}
	
	/*Envoi du message de vérification*/
	if(send(sock, messageok, strlen(messageok)+1, 0) == -1){
	
		perror("Erreur dans l'envoi du message d'erreur ");
		exit(1);
	}
	
	free(r);
}

void put(int sock, char *f, long t){
	
	int nb_recu = 0, n, fd;
	char buffer[TAILLE_BUF];
	
	printf("Lancement de la réception du fichier %s (%li octets)\n", f, t);			
	
	/*Création du fichier (écrase l'ancien s'il existe déjà)*/
	if((fd = open(f, O_CREAT|O_WRONLY|O_TRUNC), 660) == -1){

		perror("Erreur dans la création du fichier ");
		exit(1);
	}
	
	/*Appel a recv tant qu'on a pas reçu la taille de fichier requise*/
	while(nb_recu != t){
		
		n = recv(sock, buffer, TAILLE_BUF, 0);
		nb_recu += n;
		
		//On réceptionne des données
		if(n > 0){
		
			if(write(fd, &buffer, n) == -1){
		
				perror("Erreur dans l'écriture du fichier\n");
				exit(1);
			}
		}
		//Erreur dans recv
		else if(n == -1){
	
			perror("Erreur dans la réception des données\n");
			exit(1);
		}
	}
	
	/*Le fichier est reçu*/
	printf("\nLe fichier \"%s\" a été téléchargé avec succès dans le dossier %s\n", f, getcwd(NULL, 0));
	
	close(fd);
}

void get(int sock, char *f){

	RESPONSE *r;
	int fd, t_fich, i;
	char buffer[TAILLE_BUF];
	
	/*Allocation de la structure RESPONSE*/
	if((r = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
		
		perror("Erreur dans l'allocation de la structure de réponse ");
		exit(1);
	}
	
	if((fd = open(f, O_RDONLY)) == -1){
	
		perror("Erreur dans l'ouverture du fichier ");
		message_erreur(sock, "Fichier impossible à ouvrir ou inexistant");
		return;
	}
	
	//Récupération de la taille du fichier
	lseek(fd, 0, SEEK_END);
	t_fich = lseek(fd, 0, SEEK_CUR);
	lseek(fd, 0, SEEK_SET);
	
	r->code = 200;
	r->taille = t_fich;
	
	/*Envoi de la structure réponse*/
	if(send(sock, r, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans l'envoi d'une reponse erreur ");
		exit(1);
	}
	
	printf("\nEnvoi du fichier %s en cours (%i octets)\n", f, t_fich);
	
	/*Envoi du fichier*/
	while((i = read(fd, &buffer, sizeof(char)*TAILLE_BUF)) != 0 && i != -1){
		
		buffer[i] = '\0';
		
		if(send(sock, &buffer, strlen(buffer), 0) == -1){
		
			perror("Erreur dans l'envoi des données au serveur ");
			exit(1);
		}
	}
	
	if(i == -1){
		perror("Erreur dans la lecture du fichier ");
		return;
	}
	
	printf("Fichier \"%s\" envoyé avec succès au client\n", f);
	
	free(r);
}

void message_erreur(int sock, char *s){

	RESPONSE *r;
	
	/*Allocation de la structure RESPONSE*/
	if((r = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
		
		perror("Erreur dans l'allocation de la structure de réponse ");
		exit(1);
	}
	
	/*Envoi de la structure réponse*/
	r->taille = sizeof(char)*(strlen(s)+1);
	r->code = 500;
	
	if(send(sock, r, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans l'envoi d'une reponse erreur ");
		exit(1);
	}
	
	/*Envoi du message d'erreur*/
	if(send(sock, s, r->taille, 0) == -1){
	
		perror("Erreur dans l'envoi du message d'erreur ");
		exit(1);
	}
	
	free(r);
}

void quitter(int s){

	close(s);
}
