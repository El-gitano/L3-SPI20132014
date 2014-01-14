#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>

#define TAILLE 1024
#define CLE 1

/*Définition des types appel et corps d'appel*/
typedef struct corps_appel{
    
    char donnees[TAILLE];
    unsigned int num_fonc;
    pid_t pid_appelant;
}corps_appel_t;

typedef struct appel {
    long type;
    corps_appel_t corps;
}appel_t;

/*Définition du type retour*/
typedef struct retour {

    long type;
    char resultats[TAILLE];
}retour_t;

void appeler(key_t num_bibliotheque, unsigned int num_fonction, char *p_donnees, char * p_resultats);


#endif
