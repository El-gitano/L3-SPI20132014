#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

/*Énoncé : faire un serveur qui donne l'heure sur une machine
 * Un client fait une demande qu'il dépose dans une boite aux lettres. Le serveur reçoit la demande, crée la réponse, la dépose ds la BAL. Le client reçoit sa réponse ainsi.
 * on suppose que la fction date renvoit une chaine de caractères d'au plus MAX_DATE*/

#define MAX_DATE 19
#define A_SERV 42
#define CLE 11

//ce fichier fait office de message.h

typedef struct demande_s {

    long type;
    pid_t pid_client;
}demande_t;

typedef struct reponse {

    long type;
    char corps[MAX_DATE];
}reponse_t;

