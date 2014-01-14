# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = .
commun_dir = $(top_dir)/Commun
terrain_dir = $(top_dir)/Terrain
vers_dir = $(top_dir)/Vers
verrous_dir = $(top_dir)/Verrous
signaux_dir = $(top_dir)/Signaux
distrib_dir = $(top_dir)/Etudiants

all : 
	cd $(terrain_dir) ; make -f Makefile all ; cd $(top_dir)
	cd $(vers_dir) ; make -f Makefile all ; cd $(top_dir)
	cd $(commun_dir) ; make -f Makefile all ; cd $(top_dir)
	cd $(signaux_dir) ; make -f Makefile all ; cd $(top_dir)
	cd $(verrous_dir) ; make -f Makefile all ; cd $(top_dir)

clean :
	cd $(terrain_dir) ; make -f Makefile clean ; cd $(top_dir)
	cd $(vers_dir) ; make -f Makefile clean ; cd $(top_dir)
	cd $(commun_dir) ; make -f Makefile clean ; cd $(top_dir)
	cd $(signaux_dir) ; make -f Makefile clean ; cd $(top_dir)
	cd $(verrous_dir) ; make -f Makefile clean ; cd $(top_dir)

distrib : 
	cp $(terrain_dir)/*.[hc] $(terrain_dir)/Makefile $(distrib_dir)/TP_Vers/Terrain/.
	cp $(vers_dir)/*.[ch] $(vers_dir)/Makefile  $(distrib_dir)/TP_Vers/Vers/.
	cp $(commun_dir)/*.[ch] $(commun_dir)/Makefile $(distrib_dir)/TP_Vers/Commun/.
	cp $(verrous_dir)/Makefile $(distrib_dir)/TP_Vers/Verrous/.
	cp $(signaux_dir)/Makefile $(distrib_dir)/TP_Vers/Signaux/.
	cp Makefile $(distrib_dir)/TP_Vers/.
	rm -f  $(distrib_dir)/TP_Vers.tar*
	tar cvf $(distrib_dir)/TP_Vers.tar $(distrib_dir)/README $(distrib_dir)/TP_Vers 
	gzip $(distrib_dir)/TP_Vers.tar

distrib-clean :
	find $(distrib_dir)/TP_Vers \( -name '*.[ch]' -o -name 'Makefile' \) -exec rm {} \;
