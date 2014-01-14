LIBS=Exercice5.o
EXE=programme
FLAGS=-Wall -g 

${EXE}:${LIBS} 

	gcc ${LIBS} -o ${EXE} ${FLAGS} 
	
Exercice5.o:Exercice5.c

	gcc -c Exercice5.c
	
cleanobj:
	rm -f ${LIBS} 

clean:
	rm -f ${LIBS} ${EXE} 
