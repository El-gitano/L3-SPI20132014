#include "message.h"
#include <string.h>

/*code du td sur les bal donné en cours*/

void appeler( int num_bibliotheque, unsigned int num_fontion, char * donnees, char * resultats){

    int id = msgget(CLE, 0666);

    appel_t requete;
    requete.type = num_bibliotheque;
    requete.corps.num_fonc = num_fonction;
    requete.corps.pid_appelant = get_pid();
    strcpy(requete.coprs.donnees, donnees);

    /*envoi de la requete*/
    msgsnd(id, &requete, sizeof(corps_appel_t), 0);
    /*attente des resultats.*/
    retour_t rep;
    msgrcv(id, &rep, sizeof(rep.resultats), getpid(), 0);

    strcpy(resultats, rep.resultats);
}
