LIBS=Exercice2.o
EXE=Exercice2
FLAGS=-Wall -g

${EXE}:${LIBS}

	gcc ${LIBS} -o ${EXE} ${FLAGS}

Exercice2.o:Exercice2.c

	gcc -c Exercice2.c

cleanobj:
	rm -f ${LIBS}

clean:
	rm -f ${LIBS} ${EXE}
