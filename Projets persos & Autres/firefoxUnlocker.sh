#!/bin/bash

if [ -f ~/.mozilla/firefox/*.default/.parentlock ]
then
	
	rm ~/.mozilla/firefox/*.default/.parentlock
	echo "Fichier lock supprimé, firefox débloqué !"

else

	echo "Pas de fichier lock à supprimer !"
fi
