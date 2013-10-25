#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

//TD sur les tubes
//Made in Switzerland
//25/10/2013


/*Énoncé : écrire en C : un fichier toto : Nom:Prenom:numero
 * recuperer le prenom a l'aide de cat <toto>| cut -d -F2 |sort */

int td(int argc, char * argv[]){

    int tube1[2], tube2[2];
    char fichier[126];

    strcpy(fichier, argv[1];);
    
    if(pipe(tube1) || pipe(tube2)){

        perror("pb sur la creation du tube 1\n");
        exit(-1);
    }
    switch(fork()){         //Fork pour la création du fils 0, qui contient cut

        case -1 : {     //Cas d'erreur de creation du processus
                      
                      perror("Pb fork\n");
                      exit(-1);
        }
        case 0 : {      //Fils n°0 (contient la commande cut et un second fork)
            
                     close(tube1[1]);    //on ferme l'entrée écriture du tube1 car le fils0 n'écrit pas dans le tube
                     
                     close(0);          //On ferme l'entrée 0 dans la liste des descripteurs locaux.
                     dup(tube1[0]);      //on associe la lecture du tube 1 à l'entrée 0 des descrpteurs locaux
                     close(tube1[0]);       //on ferme la lecture du tube1

                     close(tube2[0]);       //Puisque le fils O ne lit pas dans tube 2, on ferme l'accès lecture du tube 2

                     close(1);              //On ferme l'entrée 1 dans la liste des descripteurs locaux
                     dup(tube2[1]);         //On associe l'entrée du tube à la première case libre de la table des descripteurs locaux, c'est à dire 1 qu'on vient de fermer
                     close(tube2[1]);       //On ferme l'accès en écriture au tube 2

                     execlp("cut", "cut", -d: , "F2", NULL);    //on execute la commande cut en donnant la liste des paramètres.
                     printf("Problème sur l'éxécution de cut\n");
                  
                 }
    }
    switch(fork()){

         case -1 :   //Cas d'erreur de creation du processus
                      
                      perror("Pb fork\n");
                      exit(-1);
                      break;
         case 0 :   //Création du fils 1, contenant sort
                      close(tube1[0]);
                      close(tube1[1]);      //on utilise pas le tube 1 dans ce processus

                      close(0);
                      dup(tube2[0]);        //on associe la lecture du tube 2 à l'entrée 0 des descripteurs locaux
                      close(tube1[0]);

                      close(tube2[1]);      //ce processus n'ecrit pas dans tube2

                      exelp("sort", "sort", NULL);      //execution de sort
                      printf("erreur dans l'execution de sort\n");
                      exit(-1);
    }
    close (tube1[0]);   //Ne lit pas dans le tube 1

    close (1);
    dup(tube1[1]);      //redirection de l'ecriture du tube1 dans l'entrée 1 des descripteurs locaux
    close(tube1[1]);

    close(tube2[0]);
    close(tube2[1]);        //n'utilise pas le tube2

    execlp("cat", "cat", Fichier, NULL);    //execution  de cat avec liste des paramètres

    printf("Pb dans l'éxecution de cat\n");

}

