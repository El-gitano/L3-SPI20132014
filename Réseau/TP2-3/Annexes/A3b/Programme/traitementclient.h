#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <ctype.h>
#include "messages.h"

#define TAILLE_BUF 20

void vider_stdin();
int lire(char *, int);
void recupererCommande(REQUEST *);
void traiterCommande(int, REQUEST *);
void lls();
void lcd();
void ls(int, REQUEST *);
void cd(int, REQUEST *);
void put(int, REQUEST *);
void get(int,REQUEST *);
void quitter(int, REQUEST *);
void afficher_message(int, int);
