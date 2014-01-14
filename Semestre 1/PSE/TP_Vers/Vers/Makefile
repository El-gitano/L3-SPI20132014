# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
commun_dir = $(top_dir)/Commun
terrain_dir = $(top_dir)/Terrain
vers_dir =  $(top_dir)/Vers

#
# Object files
#

fich_obj_init_fich_vers = init_fich_vers.o
fich_obj_test_vers = test_vers.o vers.o
fich_obj_kill_vers = kill_vers.o vers.o


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
#-------- Utilitaires ---------------
#

init_fich_vers : $(fich_obj_init_fich_vers)
	$(GCCLNK) $(fich_obj_init_fich_vers) $(opt) -o init_fich_vers -I$(commun_dir) -I$(vers_dir) 

init_fich_vers.o : init_fich_vers.c 
	$(GCCOBJ) $(opt) init_fich_vers.c -o init_fich_vers.o -I$(commun_dir) -I$(vers_dir) 

kill_vers : $(fich_obj_kill_vers)
	$(GCCLNK) $(fich_obj_kill_vers) $(opt) -o kill_vers -I$(commun_dir) -I$(vers_dir) -I$(terrain_dir)

kill_vers.o : kill_vers.c vers.h
	$(GCCOBJ) $(opt) kill_vers.c -o kill_vers.o -I$(commun_dir) -I$(vers_dir) -I$(terrain_dir)

#
# --- Tests ---
#

test_vers : $(fich_obj_test_vers)
	$(GCCLNK) $(fich_obj_test_vers) $(opt) -o test_vers -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) 

test_vers.o : test_vers.c vers.h
	$(GCCOBJ) $(opt) test_vers.c -o test_vers.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

#
#-------- Modules -------------
#

vers.o : vers.c vers.h 
	$(GCCOBJ) $(opt) vers.c -o vers.o -I$(commun_dir) -I$(terrain_dir) -I./

#
#-------- Headers -------------
#

vers.h : $(commun_dir)/commun.h $(terrain_dir)/terrain.h
	touch vers.h

#
#-------- Clean objects -------
#

clean : 
	rm -f *.o 


#
#-------- All executables -------
#

all : init_fich_vers kill_vers test_vers





