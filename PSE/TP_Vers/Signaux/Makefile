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

fich_obj_ver = ver.o $(vers_dir)/vers.o $(terrain_dir)/terrain.o
fich_obj_aire = aire.o $(vers_dir)/vers.o $(terrain_dir)/terrain.o

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
	$(GCCLNK) $(fich_obj_ver) $(opt) -o ver -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

ver.o : ver.c $(vers_dir)/vers.h $(commun_dir)/commun.h $(terrain_dir)/terrain.h
	$(GCCOBJ) $(opt) ver.c -o ver.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

aire : $(fich_obj_aire)
	$(GCCLNK) $(fich_obj_aire) $(opt) -o aire -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

aire.o : aire.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h $(vers_dir)/vers.h
	$(GCCOBJ) $(opt) aire.c -o aire.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

#
#-------- Utilitaires ---------------
#

#
# --- Tests ---
#

#
#-------- Modules -------------
#

$(terrain_dir)/terrain.o : 
	cd $(terrain_dir) ; make -f Makefile terrain.o ; cd $(signaux_dir)

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

all : ver aire 




