FLAGS=-Wall -g

all: serveur client

client: client.o

	gcc client.o -o client ${FLAGS}

client.o: client.c

	gcc -c client.c ${FLAGS}
	
serveur: serveur.o

	gcc serveur.o -o serveur ${FLAGS}
	
serveur.o: serveur.c

	gcc -c serveur.c ${FLAGS}
	
clean:

	rm -f *.o
	rm -rf Mesures

cleanall: clean

	rm -f client
	rm -f serveur
