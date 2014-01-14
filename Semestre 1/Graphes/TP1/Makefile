EXE=Exercice1
LIBS=File.o Topo.o
FLAGS= -Wall -g

${EXE}:${LIBS}

	gcc ${LIBS} -o ${EXE} ${FLAGS}

File.o:File.c

	gcc -c File.c ${FLAGS}

Topo.o:Topo.c

	gcc -c Topo.c ${FLAGS}

cleanobj:

	rm -f *.o