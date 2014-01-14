#define MAX_COMMANDE 100
#define MAX_FICHIER 1024

typedef struct req_s{

	char commande[MAX_COMMANDE];
	char fichier[MAX_FICHIER];
	long taille;
}REQUEST;

typedef struct rep_s{

	int code;
	long taille;
}RESPONSE;
