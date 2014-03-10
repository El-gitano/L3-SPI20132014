--Question 3

SELECT id_client, id_dvd FROM emprunt WHERE date_retour IS NULL AND current_date > (date_emprunt + 3);

--Question 4

CREATE OR REPLACE FUNCTION ficheclient(client_id int) RETURNS VOID AS $$

DECLARE

	dvd_liste record;
	nom_adresse record;	
	nb_emprunts int;
	
BEGIN

	--Vérification de l'existence
	SELECT nom_pers, adresse INTO nom_adresse FROM client INNER JOIN personne ON client.id_pers = personne.id_pers;
		
	IF NOT FOUND THEN
	
		RAISE EXCEPTION 'Pas de client sous l\'identifiant % !', client_id;
	
	ELSE
	
		--Affichage du nom, prénom
		RAISE NOTICE 'Nom : % - Prénom : %\n', nom_adresse.nom_pers, nom_adresse.adresse;
		
		--Nb emprunts
		nb_emprunts := (SELECT COUNT(*) FROM emprunt WHERE id_client = client_id AND date_retour IS NULL);		
		RAISE NOTICE 'Nombre d\'emprunts en cours : %', nb_dvd_empruntes;
		
		--Liste des dvds
		FOR dvd_liste IN (SELECT id_dvd, titre FROM emprunt INNER JOIN dvd ON emprunt.id_dvd = dvd.id_dvd INNER JOIN film ON film.id_film = dvd.id_film WHERE id_client = client_id AND date_retour IS NULL)
		LOOP
			
			RAISE NOTICE '% - %', dvd_liste.id_dvd, dvd_liste.titre;
			
		END LOOP;

	END IF;
END;

$$ LANGUAGE plpgsql;

SELECT ficheclient(0);

--Question 5

--Création d'une table autorisation d'emprunts

CREATE TABLE auth_emprunts(

	montant int,
	nb_dvd int,
	PRIMARY KEY (montant, nb_dvd)
	
);

INSERT INTO auth_emprunts VALUES (10, 1), (20, 2), (30, 3), (40, 4), (50, 5), (60, 6);

--Création d'un trigger et association à la table adéquate

CREATE OR REPLACE FUNCTION trig_emprunt() RETURNS TRIGGER AS $$

DECLARE

	retard record;	
	nb_emprunts int;
	nb_emprunts_aut int;
	presence_client record;
	
BEGIN

	--Vérification de la création du client
	SELECT * INTO presence_client FROM client WHERE id_client = NEW.id_client;
	
	IF NOT FOUND THEN
	
		RAISE EXCEPTION 'Le client spécifié n\'existe pas';
		
	END IF;
	
	--Vérification emprunt en retard
	SELECT * INTO retard FROM emprunt WHERE current_date > (date_emprunt + 3) AND id_client = NEW.id_client;
		
	IF FOUND THEN
	
		RAISE EXCEPTION 'Le client n\'a pas rendu certains DVDs à temps !';
	
	END IF;

	
	--Vérif emprunts
				
	--Nb emprunts actuels et autorisés
	nb_emprunts := (SELECT COUNT(*) FROM emprunt WHERE id_client = NEW.id_client AND date_retour IS NULL);
	nb_emprunts_aut := (SELECT nb_dvd FROM auth_emprunts WHERE montant = (SELECT cotisation FROM client WHERE id_pers = NEW.id_client));
		
	IF nb_emprunts >= nb_emprunts_auth THEN
		
		RAISE EXCEPTION 'Le nombre d\'emprunts autorisé pour ce client est déjà atteint';
		
	END IF;
		
	RETURN NEW;
	
END;

$$ LANGUAGE plpgsql;

CREATE TRIGGER auth_emp BEFORE INSERT ON emprunt FOR EACH ROW EXECUTE PROCEDURE trig_emprunt();

--Ajout de la fonction pour l'employé

CREATE OR REPLACE FUNCTION ajout_emprunt(id_client int, id_dvd int) RETURNS void AS $$
	
BEGIN

	INSERT INTO emprunt VALUES (DEFAULT, current_date, NULL, id_client, id_dvd);
	
END;

$$ LANGUAGE plpgsql;