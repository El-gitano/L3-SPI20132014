/*TD sur les signaux Unix*/

//Q3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NSIGe 30

int secondes = 0;
int SIG = 0;

void handler_sleep(int sig){
    
    if(sig != SIGALRM)
        secondes = alarm(0);
        SIG = sig;
}

int Sleep(int secondes){

    int i =0;
    struct sigaction action_reveil, old_action[NSIGe];
    action_reveil.sa_handler = handlep_sleep;
    action_reveil.sa_flags = 0;
    sigemptyset(action_reveil.sa_mask);
    for(i = 0; i < NSIGe, i ++){

        sigaddset(&action_reveil.sa_mask, &);
    }

    for(i =0; i< NSIGe; i ++){

        sigaction(i, action_reveil, &old_action[i]);
    }

    alarm(secondes);
    pause();
    for(i = 0; i < NSIGe; i ++){
        
        sigaction(i, old_action[i], NULL);
    }
    kill(SIG, getpid());
    return(secondes);
}
int system(char * commande){

    //masquage des signaux
    /*sigaction~~~~
    sigprocmask~~~*/

    //éxécution dans un shell de commande
    pid_t pid;
    int cr;
    switch(pid = fork()){

        case -1 :
            printf("erreur, echec du fork\n");
            exit(-1);
            break;
        case 0 :
            printf("Fils : processus N°%d", getpid());
            //utilisation des différents exec
            //execl :
            execl("/bin/sh", "sh", "-c", commande, NULL);
            //pour execv, il faut contruire le tableau de paramètre
            char * param[10];
            param[0] = "sh";
            param[1] = "-c";
            param[2] = malloc(strlen(commande)+1);
            strcpy(param[2], commande);
            param[3] = NULL;
            execv("/bin/sh",param);
            //execlp :
            execlp("sh", "sh", "-c", commande, NULL);
            //execvp :
            execvp("sh", param);
            printf("Si vous lisez ceci, c'est pas bon signe pour l'eexecution de l'exec");
        default :
            while(wait(&cr)!= pid);
            printf(" Fin du processus fils n°%d : code retour :%d\n", pid, cr);
            //restauration des signaux masqués et ignorés.
            break;
    }

}
