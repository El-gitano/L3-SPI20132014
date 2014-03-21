OUT=Test
FLAGS = -Wall -g
all:compile link cleanobj execute

execute:

	${OUT}
	
link:

	gcc *.o -o ${OUT} ${FLAGS}
	
cleanobj:

	rm *.o

compile:

	gcc -c *.c ${FLAGS}

	