# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
commun_dir = $(top_dir)/Commun
terrain_dir = $(top_dir)/Terrain
vers_dir = $(top_dir)/Vers


#
# Object files
#

fich_obj_test_jeu = test_jeu.o jeu.o $(terrain_dir)/terrain.o $(vers_dir)/vers.o


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

#
# --- Tests ---
#

test_jeu : $(fich_obj_test_jeu)
	$(GCCLNK) $(fich_obj_test_jeu) $(opt) -o test_jeu -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) 

test_jeu.o : test_jeu.c $(commun_dir)/commun.h jeu.h
	$(GCCOBJ) $(opt) test_jeu.c -o test_jeu.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) 

#
#-------- Modules -------------
#

jeu.o : jeu.c jeu.h $(commun_dir)/commun.h
	$(GCCOBJ) $(opt) jeu.c -o jeu.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

$(terrain_dir)/terrain.o : 
	cd $(terrain_dir) ; make -f Makefile terrain.o ; cd $(verrou_dir)

$(vers_dir)/vers.o : 
	cd $(vers_dir) ; make -f Makefile vers.o ; cd $(signaux_dir) 

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

all :  test_jeu 



