#include "traitementclient.h"

void vider_stdin(){

	int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        else{
        
       		vider_stdin();
       	}
        
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

void recupererCommande(REQUEST *r){

	char *commande;
	char *debut, *fin;
	int taille_chaine = sizeof(char)*(MAX_FICHIER + MAX_COMMANDE + 1);
	
	/*On alloue la chaîne qui recevra la commande*/
	if((commande = (char *)malloc(taille_chaine)) == NULL){
	
		perror("Erreur dans l'allocation dynamique ");
		exit(1);
	}
	
	/*On récupère la commande*/
	printf("\n\nVeuillez entrer votre commande : \n\n > ");
	lire(commande, taille_chaine);

	/*On la parse pour remplir la structure REQUEST*/
	debut = commande;

	//On parcourt la chaîne jusqu'à atteindre la taille MAX du champs commande ou atteindre la fin de la commande
	for(fin = debut; isgraph(*fin) && ((fin-debut)/sizeof(char)) < (MAX_COMMANDE) ; fin += 1);
	
	strncpy(r->commande, commande, fin-debut);
	r->commande[(fin-debut)] = '\0';

	//On a un deuxième paramètre (le fichier)
	if(*fin != '\0'){
	
		debut = fin+1;
		for(fin = debut; isgraph(*fin) && ((fin-debut)/sizeof(char)) < (MAX_FICHIER-1) ; fin++);
	
		strncpy(r->fichier, debut, fin-debut);
		r->fichier[(fin-debut)] = '\0';
		
	}
	
	free(commande);
}

void traiterCommande(int socket, REQUEST *r){

	if(strcmp(r->commande, "lls") == 0){
	
		lls();
	}
	else if(strcmp(r->commande, "lcd") == 0){
	
		lcd(r->fichier);
	}
	else if(strcmp(r->commande, "ls") == 0){
	
		ls(socket, r);
	}
	else if(strcmp(r->commande, "cd") == 0){
	
		cd(socket, r);
	}
	else if(strcmp(r->commande, "get") == 0){
	
		get(socket, r);
	}
	else if(strcmp(r->commande, "put") == 0){
	
		put(socket, r);
	}
	else if(strcmp(r->commande, "exit") == 0){
	
		quitter(socket, r);
	}
	else{
		
		printf("Commande inconnue : %s\n", r->commande);
	}
}

void lls(){

	DIR *d;
	struct dirent *entree;
	
	/*Ouverture du dossier actuel*/
	if((d = opendir(".")) == NULL){
	
		perror("Erreur dans l'ouverture du dossier actuel ");
		return;
	}
	
	while((entree = readdir(d)) != NULL){
	
		printf("\t%s\n", entree->d_name);
	}
	
	/*Nettoyage*/
	closedir(d);
}

void lcd(char *f){

	printf("Tentative de déplacement vers le dossier %s\n\n", f);
	
	if(chdir(f) == -1){
	
		perror("Erreur dans le changement de dossier courant ");
		return;
	}
	
	printf("Dossier courant changé, nouveau dossier courant : %s\n", getcwd(NULL, 0));
}

void quitter(int sock, REQUEST *r){

	//On envoi la requête de déconnexion
	if(send(sock, r, sizeof(REQUEST), 0) == -1){
	
		perror("Erreur dans l'envoi des données de déconnexion ");
		exit(1);
	}
	
	//On ferme le socket et on quitte le programme
	printf("\nRequête de déconnexion envoyée\n");	
	close(sock);
	
	exit(0);
}

void ls(int sock, REQUEST *r){

	RESPONSE *p;
	char *mess;
	int nb_entrees;
	unsigned short t_ent;
	
	/*Allocation de la structure de réponse*/
	if((p = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
	
		perror("Erreur dans l'allocation dynamique d'une struture de réponse ");
		exit(1);
	}
	
	//On envoi la requête
	if(send(sock, r, sizeof(REQUEST), 0) == -1){
	
		perror("Erreur dans l'envoi des données de consultation du dossier distant ");
		exit(1);
	}

	//On réceptionne la réponse
	if(recv(sock, p, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans la réception de la réponse ");
		exit(1);
	}	
	
	/*On affiche si la requête s'est déroulée correctement*/
	if(p->code == 200){
	
		printf("\n\n\t---REQUETE OK---\n\n");
		
	}
	else if(p->code == 500){
	
		printf("\n\n\t---ERREUR---\n\n");
	}
	
	/*On récupère le nombre de fichiers à afficher*/
	if(recv(sock, &nb_entrees, sizeof(int), 0) == -1){
	
		perror("Erreur dans la réception du nombre d'entrées ");
		exit(1);
	}
	
	printf("Nombre d'entrées : %i\n\n", nb_entrees);
	
	while(nb_entrees != 0){
	
		/*On récupère la taille de l'entrée*/
		if(recv(sock, &t_ent, sizeof(unsigned short), 0) == -1){
	
			perror("Erreur dans la réception de la taille de l'entrée ");
			exit(1);
		}
		
		/*On alloue l'espace nécessaire*/
		if((mess = (char *)malloc(sizeof(char)*t_ent)) == NULL){
		
			perror("Erreur dans l'allocation de la mémoire pour l'entrée ");
			exit(1);
		}
		
		/*On récupère l'entrée et on l'affiche*/
		if(recv(sock, mess, sizeof(char)*t_ent, 0) == -1){
	
			perror("Erreur dans la réception de l'entrée ");
			exit(1);
		}
		
		printf("\t%s\n", mess);
		
		/*Nettoyage*/	
		free(mess);
		nb_entrees--;
	}
	
	free(p);
}

void cd(int sock, REQUEST *r){

	RESPONSE *p;
	
	/*Allocation de la structure de réponse*/
	if((p = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
	
		perror("Erreur dans l'allocation dynamique d'une struture de réponse ");
		exit(1);
	}
	
	//On envoi la requête
	if(send(sock, r, sizeof(REQUEST), 0) == -1){
	
		perror("Erreur dans l'envoi des données de changement du dossier ");
		exit(1);
	}
	
	//On réceptionne la réponse
	if(recv(sock, p, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans la réception de la réponse ");
		exit(1);
	}
	
	/*On affiche si la requête s'est déroulée correctement*/
	if(p->code == 200){
	
		printf("\n\n\t---REQUETE OK---\n\n");
		
	}
	else if(p->code == 500){
	
		printf("\n\n\t---ERREUR---\n\n");
	}
	
	afficher_message(sock, p->taille);
	
	free(p);
}

void get(int sock, REQUEST *r){

	RESPONSE *p;
	int taille_f;
	char buffer[TAILLE_BUF];
	int fd, n, nb_recu = 0;
	
	/*Allocation de la structure de réponse*/
	if((p = (RESPONSE *)malloc(sizeof(RESPONSE))) == NULL){
	
		perror("Erreur dans l'allocation dynamique d'une struture de réponse ");
		exit(1);
	}
	
	/*On envoi la requête pour demander le fichier*/
	if(send(sock, r, sizeof(REQUEST), 0) == -1){
	
		perror("Erreur dans l'envoi des données d'envoi d'un fichier ");
		exit(1);
	}
	
	/*On réceptionne la réponse*/
	if(recv(sock, p, sizeof(RESPONSE), 0) == -1){
	
		perror("Erreur dans la réception de la réponse ");
		exit(1);
	}
	
	/*On affiche si la requête s'est déroulée correctement et on récupère la taille du fichier*/
	if(p->code == 200){
	
		printf("\n\n\t---REQUETE OK---\n\n");
		taille_f = p->taille;
		printf("Lancement de la réception du fichier %s (%i octets)\n", r->fichier, taille_f);			
	}
	else if(p->code == 500){
	
		printf("\n\n\t---ERREUR---\n\n");
		afficher_message(sock, p->taille);
		free(p);
		return;
	}
	
	/*Création du fichier (écrase l'ancien s'il existe déjà)*/
	if((fd = open(r->fichier, O_RDWR|O_CREAT|O_TRUNC), 660) == -1){

		perror("Erreur dans la création du fichier ");
		exit(1);
	}
	
	/*Appel a recv tant qu'on a pas reçu la taille de fichier requise*/
	while(nb_recu != taille_f){
		
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
	printf("\nLe fichier \"%s\" a été téléchargé avec succès dans le dossier %s\n", r->fichier, getcwd(NULL, 0));
	
	close(fd);
	free(p);
}

void put(int sock, REQUEST *r){

	char buffer[TAILLE_BUF];
	int fd, i, t_fich;
	
	if((fd = open(r->fichier, O_RDONLY)) == -1){
	
		perror("Erreur dans l'ouverture du fichier ");
		return;
	}
	
	//Récupération de la taille du fichier
	lseek(fd, 0, SEEK_END);
	t_fich = lseek(fd, 0, SEEK_CUR);
	lseek(fd, 0, SEEK_SET);
	
	r->taille = t_fich;
	
	/*Envoi de la structure réponse*/
	if(send(sock, r, sizeof(REQUEST), 0) == -1){
	
		perror("Erreur dans l'envoi d'une reponse erreur ");
		exit(1);
	}
	
	printf("\nEnvoi du fichier %s en cours (%i octets)\n", r->fichier, t_fich);
	
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
	
	printf("Fichier \"%s\" envoyé avec succès au serveur\n", r->fichier);
}

void afficher_message(int sock, int t){

	char *mess;
	
	/*On alloue l'espace mémoire pour le message de réponse*/
	if((mess = (char *)malloc(sizeof(char)*(t))) == NULL){
	
		perror("Erreur dans l'allocation de la mémoire pour le message de réponse ");
		exit(1);
	}
	
	/*On réceptionne le message de réponse et on l'affiche*/
	if(recv(sock, mess, t, 0) == -1){
	
		perror("Erreur dans la réception de la réponse ");
		exit(1);
	}
	
	printf("%s", mess);
	
	free(mess);
}
