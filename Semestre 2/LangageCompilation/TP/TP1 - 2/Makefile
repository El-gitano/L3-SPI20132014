OUT1=Test1
OUT2=Test2
FLAGS = -Wall -g
LIBS1 = Alex.c Asynth.c main.c
OBJET1 = Alex.o Asynth.o main.o
LIBS2 = AlexC.c main2.c
OBJ2 = AlexC.o main2.o

all:execute1 execute2

execute1: compile1 link1

	${OUT1}

execute2: compile2 link2

	${OUT2}
		
link1:${OBJET1}

	gcc ${OBJET1} -o ${OUT1} ${FLAGS}

link2:${OBJET2}

	gcc ${OBJ2} -o ${OUT2} ${FLAGS}
	
compile1:${LIBS1}

	gcc -c ${LIBS1} ${FLAGS}

compile2:${LIBS2}

	gcc -c ${LIBS2} ${FLAGS}

cleanobj:

	rm *.o