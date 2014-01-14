LIBS=Exercice3.o
EXE=Exercice3
FLAGS=-Wall -g

${EXE}:${LIBS}

	gcc ${LIBS} -o ${EXE} ${FLAGS}

Exercice3.o:Exercice3.c

	gcc -c Exercice3.c

cleanobj:
	rm -f ${LIBS}

clean:
	rm -f ${LIBS} ${EXE}
