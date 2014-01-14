LIBS=Exercice1.o
EXE=programme
FLAGS=-Wall -g 

${EXE}:${LIBS} 

	gcc ${LIBS} -o ${EXE} ${FLAGS} 
	
Exercice1.o:Exercice1.c

	gcc -c Exercice1.c
	
cleanobj:
	rm -f ${LIBS} 

clean:
	rm -f ${LIBS} ${EXE} 
