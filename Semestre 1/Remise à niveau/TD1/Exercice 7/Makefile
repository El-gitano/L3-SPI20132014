LIBS=Exercice7.o
EXE=programme
FLAGS=-Wall -g 

${EXE}:${LIBS} 

	gcc ${LIBS} -o ${EXE} ${FLAGS} 
	
Exercice7.o:Exercice7.c

	gcc -c Exercice7.c
	
cleanobj:
	rm -f ${LIBS} 

clean:
	rm -f ${LIBS} ${EXE} 
