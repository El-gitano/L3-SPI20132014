# MAKEFILE pour Cours sur les files de messages
#
#

#
# Directories
#
top_dir = .


#
# Object files
#

fich_obj_coureur = coureur.o messages.o

#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 


# Option for debugger
opt = -g -Wall -D_DEBUG_
# opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

coureur : $(fich_obj_coureur)
	$(GCCLNK) $(fich_obj_coureur) $(opt) -o coureur -I ./

coureur.o : coureur.c 
	$(GCCOBJ) $(opt) coureur.c -o coureur.o -I ./

#
# --- Tests ---
#

#
#-------- Modules -------------
#


messages.o : messages.c messages.h 
	$(GCCOBJ) $(opt) messages.c -o messages.o -I ./

#
#-------- Headers -------------
#

#
#-------- Clean objects -------
#

clean : 
	rm -f *.o 

#
#-------- All executables -------
#

all :   coureur 

#
#-------- All tests -------
#

#
#-------- Tags -------
#

tags :
	etags *.c 
