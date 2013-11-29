# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
commun_dir = $(top_dir)/Commun
terrain_dir = $(top_dir)/Terrain
verrou_dir = $(top_dir)/Verrous
vers_dir = $(top_dir)/Vers

#
# Object files
#

fich_obj_ver = ver.o $(terrain_dir)/terrain.o $(commun_dir)/jeu.o
fich_obj_vision = vision.o $(terrain_dir)/terrain.o


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

ver : $(fich_obj_ver)
	$(GCCLNK) $(fich_obj_ver) $(opt) -o ver -I$(commun_dir) -I$(terrain_dir)

ver.o : ver.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h $(commun_dir)/jeu.h
	$(GCCOBJ) $(opt) ver.c -o ver.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir)

vision : $(fich_obj_vision)
	$(GCCLNK) $(fich_obj_vision) $(opt) -o vision -I$(commun_dir) -I$(terrain_dir)

vision.o : vision.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h
	$(GCCOBJ) $(opt) vision.c -o vision.o -I$(commun_dir) -I$(terrain_dir)

#
# --- Tests ---
#


#
#-------- Modules -------------
#

$(terrain_dir)/terrain.o : 
	cd $(terrain_dir) ; make -f Makefile terrain.o ; cd $(verrou_dir)

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

all : ver vision

#
#-------- All tests -------
#

all-test :




