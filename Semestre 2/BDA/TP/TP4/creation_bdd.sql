--Script de création des tables pour le TP n°4

/*		Supression des tables et du schéma existants pour la création 		*/

DROP SCHEMA IF EXISTS tp_dvd CASCADE;

/*		Création d'un schéma pour le TP et insertion dans le search_path		*/

CREATE SCHEMA tp_dvd;
SET search_path TO tp_dvd, "$user",public;


/*		Création des tables		*/

--Table Personne
CREATE TABLE personne (

	id_pers serial PRIMARY KEY,
	nom_pers varchar(60) NOT NULL,
	prenom_pers varchar(60) NOT NULL
);

--Table Magasin
CREATE TABLE magasin (

	id_magasin serial PRIMARY KEY,
	adresse varchar(100)
);

--Table Client
CREATE TABLE client (

	id_pers int PRIMARY KEY REFERENCES personne(id_pers),
	adresse varchar(100) NOT NULL,
	cotisation int NOT NULL
);

--Table Genre
CREATE TABLE genre(

	id_genre serial PRIMARY KEY,
	nom varchar(60) NOT NULL,
	public varchar(50) NOT NULL	
);

--Table Film
CREATE TABLE film (

	id_film serial PRIMARY KEY,
	duree int NOT NULL,
	titre varchar(100) NOT NULL,
	genre int REFERENCES genre(id_genre),
	realisateur int REFERENCES personne(id_pers)
);

--Table Réaliser (Si relation réalisation != 1-1)
/*CREATE TABLE realiser (

	id_pers int,
	id_film int,
	
	PRIMARY KEY (id_pers, id_film),
	FOREIGN KEY (id_pers) REFERENCES personne(id_pers),
	FOREIGN KEY (id_film) REFERENCES film(id_film)
);*/

--Table Jouer
CREATE TABLE jouer (

	id_jouer serial PRIMARY KEY,
	id_pers int REFERENCES personne(id_pers),
	id_film int REFERENCES film(id_film)
);

--Table DVD
CREATE TABLE dvd (

	id_dvd serial PRIMARY KEY,
	etat varchar(30) NOT NULL,
	date_mes date NOT NULL,
	film int REFERENCES film(id_film),
	id_magasin int REFERENCES magasin(id_magasin)
);

--Table Emprunt
CREATE TABLE emprunt (

	id_emprunt serial PRIMARY KEY,
	date_emprunt date NOT NULL,
	date_retour date,
	id_client int REFERENCES personne(id_pers),
	id_dvd int REFERENCES dvd(id_dvd)	
);


/*		Affichage de vérification		*/

SHOW search_path;
\dt tp_dvd.*