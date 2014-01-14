#============================
# Makefile du Cours 2 / FILE
#============================


#-------------
# Executables 
#-------------

testfile : testfile.o eltprim.o fileprim.o 
	gcc testfile.o eltprim.o fileprim.o  -o testfile

testfile.o : testfile.c
	gcc -c testfile.c -o testfile.o 

#----------
# Modules
#----------

# TDA ELEMENT
#

# -- Primitives avec realisation par "int"
#
eltprim.o : eltint.c eltprim.h
	gcc -c eltint.c -o eltprim.o

eltprim.h : eltsdd.h
	touch eltprim.h

eltsdd.h : eltint.h
	touch eltsdd.h

# -- Operations 
#

# TDA FFILE
#

# -- Primitives avec realisation par faux pointeurs : 
#

fileprim.o : filtabci.c fileprim.h
	gcc -c filtabci.c -o fileprim.o

fileprim.h : filesdd.h 
	touch fileprim.h

filesdd.h : filtabci.h 
	touch filesdd.h

# -- Operations 
#

#----------------------------
# Gestion generale du projet 
#----------------------------

all : testfile

clean :
	rm *.o

tags : 
	etags *.c *.h
