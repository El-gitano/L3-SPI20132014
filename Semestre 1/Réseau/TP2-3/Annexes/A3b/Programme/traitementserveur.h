#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include "messages.h"

#define TAILLE_BUF 20

int traiterCommande(int, REQUEST *);
void ls(int);
void cd(int, char *);
void put(int, char *, long);
void get(int, char *);
void message_erreur(int, char *);
void quitter(int);
