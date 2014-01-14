LIBS=Exercice8.o
EXE=programme
FLAGS=-Wall -g 

${EXE}:${LIBS} 

	gcc ${LIBS} -o ${EXE} ${FLAGS} 
	
Exercice8.o:Exercice8.c

	gcc -c Exercice8.c
	
cleanobj:
	rm -f ${LIBS} 

clean:
	rm -f ${LIBS} ${EXE} 
