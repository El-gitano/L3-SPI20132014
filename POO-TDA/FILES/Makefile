#
# Executables à rajouter vous memes 



#----------
# Modules
#----------

# TDA ELEMENT
#

# -- Primitives (possibilité de modifier le type d'ELEMENT)
#
eltprim.o : elt.c eltprim.h
	gcc -c elt.c -o eltprim.o

eltprim.h : eltsdd.h
	touch eltprim.h

eltsdd.h : elt.h
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
