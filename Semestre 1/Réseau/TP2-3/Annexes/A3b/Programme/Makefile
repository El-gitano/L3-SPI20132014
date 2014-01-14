FLAGS=-Wall -g

all: serveur client

serveur:serveur.o traitementserveur.o

	gcc serveur.o traitementserveur.o -o serveur ${FLAGS}

serveur.o: serveur.c messages.h traitementserveur.h

	gcc -c serveur.c ${FLAGS}
	
traitementserveur.o: traitementserveur.c messages.h traitementserveur.h

	gcc -c traitementserveur.c ${FLAGS}
	
client: client.o traitementclient.o

	gcc client.o traitementclient.o -o client ${FLAGS}
	
traitementclient.o : traitementclient.c messages.h traitementclient.h

	gcc -c traitementclient.c ${FLAGS}

client.o : client.c messages.h traitementclient.h
	
	gcc -c client.c ${FLAGS} 
	
cleanobj :

	rm *.o
	
cleanexes :

	rm serveur
	rm client
	
cleanall : cleanobj cleanexes
