LIBS=Exercice6.o
EXE=programme
FLAGS=-Wall -g 

${EXE}:${LIBS} 

	gcc ${LIBS} -o ${EXE} ${FLAGS} 
	
Exercice6.o:Exercice6.c

	gcc -c Exercice6.c
	
cleanobj:
	rm -f ${LIBS} 

clean:
	rm -f ${LIBS} ${EXE} 
