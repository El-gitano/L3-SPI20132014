/*Fichier client.c du TD de Programmation système sur les Boîtes aux Lettres
 * Made In Switzerland
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msh.h>
#include "message.h"


int main (){

    demande_t D;
    reponse_t R
    int id_bal = msgget(CLE, 0666);

    D.type = A_SERV;
    D.pid_client = getpid()

/*Dépot de la demande d'heure*/
    msgsnd(id_bal, &D, sizeof(pid_t), 0);

/*Attente de la réponse*/
    msgrcv(id_bal, &R, sizeof(char) * MAX_DATE, getpid(), 0);

/*Affichage de la réponse*/
    printf("La date est : %s\n", R.corps);

    return EXIT_SUCCESS;
}
