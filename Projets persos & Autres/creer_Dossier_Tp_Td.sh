#!/bin/bash

echo -e "\nCe petit script vous permettra de créer automatiquement vos dossiers de travail en TD-TP."

choix=""
n_tdp=0
n_exos=0

while [ "$choix" != "d" ] && [ "$choix" != "p" ]
do
	echo -e "\n"
	read -p "Voulez vous générer un dossier de TD (d) ou de TP (p) ? " -n 1 choix
done

if [ "$choix" == "d" ]
then
	dossier="TD"
else
	dossier="TP"
fi

while [ $n_tdp -lt 1 ]
do
	echo -e "\n"
	read -p "Entrez le numéro du $dossier : " -n 1 n_tdp
done

while [ $n_exos -lt 1 ]
do
	echo -e "\n"
	read -p "Entrez le nombre d'exercices du $dossier : " -n 2 n_exos
done

mkdir "$dossier$n_tdp"

cd "$dossier$n_tdp"

while [ $n_exos -gt 0 ]
do
	mkdir "Exercice $n_exos"
	
	#Ecriture des fichiers s'ils n'existent pas
	
	file="Exercice $n_exos/Exercice$n_exos.c"
	
	if ! [ -f "$file" ] 
	then
		echo -e "#include <stdlib.h>" > "$file"
		echo -e "#include <stdio.h>" >> "$file"
		echo -e "#include <ctype.h>" >> "$file"
		echo -e "#include <time.h>\n" >> "$file"
		echo -e "int main(){\n\n\treturn EXIT_SUCCESS;\n}">> "$file"
	fi
	
	file="Exercice $n_exos/Makefile"
	
	if ! [ -f "$file" ]
	then
		echo -e "LIBS=Exercice$n_exos.o" > "$file"
		echo -e "EXE=Exercice$n_exos" >> "$file"
		echo -e "FLAGS=-Wall -g\n">> "$file"
		echo -e "\${EXE}:\${LIBS}\n">> "$file"
		echo -e "\tgcc \${LIBS} -o \${EXE} \${FLAGS}\n">> "$file"
		echo -e "Exercice$n_exos.o:Exercice$n_exos.c\n">> "$file"
		echo -e "\tgcc -c Exercice$n_exos.c\n">> "$file"
		echo -e "cleanobj:">> "$file"
		echo -e "\trm -f \${LIBS}\n">> "$file"
		echo -e "clean:">> "$file"
		echo -e "\trm -f \${LIBS} \${EXE}">> "$file"
	fi
	
	let "n_exos=n_exos-1"
done

echo -e "\nDossiers crées !\n"
