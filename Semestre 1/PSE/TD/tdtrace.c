#include <stdio.h>
#include <stdlib.h>

/*On a n ateliers, comprenant chacun i capteurs. Ceux ci captent la creation d'une piece n°i. Ils l'indiquent à une centrale, qui l'ecrit dans un fichier trace*/

void capteur(int i){

    int si
    switch(i){
    
    case 1: 
        si = SIGUSR1;
        break;
    case 2 :
        si = SIGUSR2;
        break;
    case 3 :
        si = SIGINT;
        break;
    case 4 :
        si = SIGQUIT;
        break;
    }
    kill(si, pidCentrale);
}

void ecriture(int s){

    int fd = open(FICHIER_TRACE, 0_RDWR, 0666);

    switch(s){

        case SIGUSR1 :
            lseek(fd, 0, O);
            read(fd, &cpt, sizeof(int));
            lseek(fd, 0, 0);
            printenreg(fd, cpt);
            break;

        case SIGUSR2 :
            lseek(fd, TAILLE_ENREG *2, 0);
            //meme qu'au dessus
            break;
        case SIGINT :
            lseek(fd, TAILLE_ENREG*3, 0);
            //
            break;
        case SIGQUIT :
            lseek(fd, TAILLE_ENREG * 4, 0);
            //
            break;
    }
}

int main (){
    struct sigaction a;
    a.sa_hand = ecriture;
    a.sa_flags = 0;
    sigemptyset(&a.sa_mask);
    sigaddset(&a.sa_mask, SIGUSR1);
    sigaddset(&a.sa_mask, SIGUSR2);
    sigaddset(&a.sa_mask, SIGINT);
    sigaddset(&a.sa_mask, SIGQUIT);
    sigaction(




}
