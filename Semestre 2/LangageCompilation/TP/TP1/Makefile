OUT1=Test1
OUT2=Test2
FLAGS = -Wall -g
LIBS1 = Alex.c Alex.h main.c
OBJET1 = Alex.o main.o
LIBS2 = AlexC.c Alex.h main2.c
OBJ2 = AlecC.o main2.o
all:compile1 compile2 link1 link2 cleanobj execute

execute:

	${OUT1}
	echo 'Deuxième programme'
	${OUT2}
	
link1:

	gcc ${OBJET1} -o ${OUT1} ${FLAGS}

link2:

	gcc ${OBJ2} -o ${OUT2} ${FLAGS}

cleanobj:

	rm *.o

compile1:

	gcc -c ${LIBS1} ${FLAGS}

compile2:

	gcc -c ${LIBS2} ${FLAGS}
