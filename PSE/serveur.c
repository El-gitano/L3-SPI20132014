/*Fichier serveur.c du td sur les Boîtes Aux Lettres 06/11/2013
 * Made in Switzerland
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msh.h>
#include "message.h"
#include <string.h>
#include <signal.h>

/*Variable globale*/
int arret;

void hand_int(int s){

    /*msgctl(id, IPC_RMID, 0);*/
    arret = 1;
}


int main(){

    demande_t D;
    reponse_t R;
    /*Création boite aux lettres*/
    int id = msgget(CLE, 0666, IPC_CREATE);

    /*signal(SIGINT, hand_int);*/

    while(!arret){

/*Reception de la demande*/
        msgrcv(id, &D, sizeof(pid_t), A_SERV, 0);
/*Traitement de la demande*/
        strcpy(R.corps, date());
/*Envoie de la réponse*/
        R.type = D.pid_client;
        msgsnd(id, &R, sizeof(char) * MAX_DATE, 0);

    }/*Fin de la boucle while*/

/*Destruction de la boîte aux lettres*/

    msgctl(id, IPC_RMID, 0);
    exit(0);
}
