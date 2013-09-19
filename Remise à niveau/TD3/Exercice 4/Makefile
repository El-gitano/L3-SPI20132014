LIBS=Exercice4.o
EXE=Exercice4
FLAGS=-Wall -g

${EXE}:${LIBS}

	gcc ${LIBS} -o ${EXE} ${FLAGS}

Exercice4.o:Exercice4.c

	gcc -c Exercice4.c

cleanobj:
	rm -f ${LIBS}

clean:
	rm -f ${LIBS} ${EXE}
