# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
commun_dir = $(top_dir)/Commun
terrain_dir = $(top_dir)/Terrain


#
# Object files
#

fich_obj_test_terrain = test_terrain.o terrain.o 
fich_obj_init_fich_terrain = init_fich_terrain.o terrain.o 

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

init_fich_terrain : $(fich_obj_init_fich_terrain)
	$(GCCLNK) $(fich_obj_init_fich_terrain) $(opt) -o init_fich_terrain -I$(commun_dir) -I$(terrain_dir)

init_fich_terrain.o : init_fich_terrain.c $(commun_dir)/commun.h terrain.h
	$(GCCOBJ) $(opt) init_fich_terrain.c -o init_fich_terrain.o -I$(commun_dir) -I$(terrain_dir)

#
# --- Tests ---
#

test_terrain : $(fich_obj_test_terrain)
	$(GCCLNK) $(fich_obj_test_terrain) $(opt) -o test_terrain -I$(commun_dir) -I$(terrain_dir)

test_terrain.o : test_terrain.c $(commun_dir)/commun.h terrain.h
	$(GCCOBJ) $(opt) test_terrain.c -o test_terrain.o -I$(commun_dir) -I$(terrain_dir)

#
#-------- Modules -------------
#

terrain.o : terrain.c terrain.h $(commun_dir)/commun.h
	$(GCCOBJ) $(opt) terrain.c -o terrain.o -I$(commun_dir) -I$(terrain_dir)

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

all : init_fich_terrain test_terrain 



