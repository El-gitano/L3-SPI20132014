# MAKEFILE pour TP IPC
#
#

#
# Directories
#

#
# Object files
#

fich_obj_test_msg_messages = test_msg_messages.o msg_messages.o
fich_obj_msg_emetteur = msg_emetteur.o msg_messages.o
fich_obj_msg_recepteur = msg_recepteur.o msg_messages.o

fich_obj_test_pipe_messages = test_pipe_messages.o pipe_messages.o
fich_obj_pipe_emetteur = pipe_emetteur.o pipe_messages.o
fich_obj_pipe_recepteur = pipe_recepteur.o pipe_messages.o


#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 


# Option for debugger
# -- pour versions des programmes en debuggage
opt = -g -Wall -D_DEBUG_ -D_LINUX_
# -- pour versions finales des programmes  
#opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

test_msg_messages : $(fich_obj_test_msg_messages)
	$(GCCLNK) $(fich_obj_test_msg_messages) $(opt) -o test_msg_messages -I ./

test_msg_messages.o : test_msg_messages.c
	$(GCCOBJ) $(opt) test_msg_messages.c -o test_msg_messages.o -I ./

msg_emetteur : $(fich_obj_msg_emetteur)
	$(GCCLNK) $(fich_obj_msg_emetteur) $(opt) -o msg_emetteur -I ./

msg_emetteur.o : msg_emetteur.c
	$(GCCOBJ) $(opt) msg_emetteur.c -o msg_emetteur.o -I ./

msg_recepteur : $(fich_obj_msg_recepteur)
	$(GCCLNK) $(fich_obj_msg_recepteur) $(opt) -o msg_recepteur -I ./

msg_recepteur.o : msg_recepteur.c 
	$(GCCOBJ) $(opt) msg_recepteur.c -o msg_recepteur.o -I ./

test_pipe_messages : $(fich_obj_test_pipe_messages)
	$(GCCLNK) $(fich_obj_test_pipe_messages) $(opt) -o test_pipe_messages -I ./

test_pipe_messages.o : test_pipe_messages.c
	$(GCCOBJ) $(opt) test_pipe_messages.c -o test_pipe_messages.o -I ./

pipe_emetteur : $(fich_obj_pipe_emetteur)
	$(GCCLNK) $(fich_obj_pipe_emetteur) $(opt) -o pipe_emetteur -I ./

pipe_emetteur.o : pipe_emetteur.c
	$(GCCOBJ) $(opt) pipe_emetteur.c -o pipe_emetteur.o -I ./

pipe_recepteur : $(fich_obj_pipe_recepteur)
	$(GCCLNK) $(fich_obj_pipe_recepteur) $(opt) -o pipe_recepteur -I ./

pipe_recepteur.o : pipe_recepteur.c 
	$(GCCOBJ) $(opt) pipe_recepteur.c -o pipe_recepteur.o -I ./

#
# --- Tests ---
#

#
#-------- Modules -------------
#

msg_messages.o : msg_messages.c msg_messages.h 
	$(GCCOBJ) $(opt) msg_messages.c -o msg_messages.o -I ./

pipe_messages.o : pipe_messages.c pipe_messages.h 
	$(GCCOBJ) $(opt) pipe_messages.c -o pipe_messages.o -I ./

#
#-------- Headers -------------
#

msg_messages.h : messages.h
	touch msg_messages.h

pipe_messages.h : messages.h
	touch pipe_messages.h

#
#-------- Clean objects -------
#

clean : 
	- rm *.o 
	- rm *~ 

dist :
	- rm msg_recepteur ; 
	- rm msg_emetteur ; 
	- rm pipe_recepteur ; 
	- rm pipe_emetteur ; 
	- rm test_msg_messages ; 
	- rm test_pipe_messages ; 
	- rm TUBE
	- rm *.o 
	- rm *~
	cd .. ;  mv Etudiant TP_Tubes_MSG ; tar cvfz TP_Tubes_MSG.tar.gz TP_Tubes_MSG ; mv TP_Tubes_MSG Etudiant 

#
#-------- All executables -------
#

all : msg_emetteur msg_recepteur pipe_emetteur  pipe_recepteur test_msg_messages test_pipe_messages

#
#-------- All tests -------
#
tests : 
	./test_msg_messages
	./test_pipe_messages

#
#-------- Tags -------
#

tags :
	etags *.c 
