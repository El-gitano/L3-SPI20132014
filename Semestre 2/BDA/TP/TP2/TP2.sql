--Question 1

--CREATE DATABASE spi3332 WITH OWNER = spi3332 ENCODING = UTF8;

--Question 2

--ALTER ROLE spi3332 WITH ENCRYPTED PASSWORD 'azerty';

--CREATE ROLE spi3251 WITH ROLE spi3332, spi3351;
--ALTER GROUP spi3251 ADD USER spi3332, spi3351;

--Question 3

--CREATE SCHEMA AUTHORIZATION spi3332;
--CREATE SCHEMA spi3351;
--CREATE SCHEMA spi3251;

--Question 4

--SET search_path TO "$user", spi3251, spi3351, cd_jazz, public;

--Question 5

--Empêcher tout accès à la bdd de l'extérieur
--REVOKE ALL ON DATABASE spi3332 FROM PUBLIC;

--Changer propriétaires
--ALTER SCHEMA spi3332 OWNER TO spi3332;
--ALTER SCHEMA spi3251 OWNER TO spi3251;
--ALTER SCHEMA spi3351 OWNER TO spi3251;

--Donner tous les droits au binome sur le schema partagé et son schema
--GRANT ALL ON SCHEMA spi3251 TO spi3251;
--GRANT ALL ON SCHEMA spi3351 TO spi3251;

--Enlever tous les droits sur les autres schemas + lecture au binome
--REVOKE ALL ON SCHEMA spi3332, cd_jazz, public FROM PUBLIC;
--GRANT USAGE ON SCHEMA spi3332, cd_jazz, public TO spi3251;

--Création de tables
--CREATE TABLE spi3332.latable (id integer);
--CREATE TABLE spi3251.latable (id integer);
--CREATE TABLE spi3351.latable (id integer);

--Question 6

--ALTER TABLE cd_jazz.cd ADD COLUMN id_leader int;
--ALTER TABLE cd_jazz.cd ADD FOREIGN KEY (id_leader) REFERENCES cd_jazz.personne(id_pers);
--UPDATE cd_jazz.cd SET id_leader = (SELECT id_leader FROM cd_jazz.leader WHERE cd_jazz.cd.id_cd = cd_jazz.leader.id_cd) LIMIT 1 OFFSET 0;
--DROP TABLE cd_jazz.leader;

--ALTER TABLE cd_jazz.enregistrement ADD COLUMN id_compositeur int;
--ALTER TABLE cd_jazz.enregistrement ADD FOREIGN KEY (id_compositeur) REFERENCES cd_jazz.personne(id_pers);
--UPDATE cd_jazz.enregistrement SET id_compositeur = (SELECT id_compositeur FROM cd_jazz.compositeur WHERE (cd_jazz.enregistrement.id_cd, cd_jazz.enregistrement.id_enr) = (cd_jazz.compositeur.id_cd, cd_jazz.compositeur.id_enr) LIMIT 1 OFFSET 0);
--DROP TABLE cd_jazz.compositeur;

--ALTER TABLE cd_jazz.pays ADD COLUMN continent char varying(60);
--UPDATE cd_jazz.pays SET continent = 'Amérique' WHERE nom_pays = 'USA';
--UPDATE cd_jazz.pays SET continent = 'Europe' WHERE nom_pays = 'France';

--Question 7

/*
ALTER TABLE cd_jazz.personne ALTER COLUMN date_nais SET NOT NULL;
ALTER TABLE cd_jazz.personne ADD CONSTRAINT date_check CHECK(date_nais < date_deces);

--Pour éviter un problème lors de la création de la contrainte
UPDATE personne SET nom_pers = initcap(nom_pers);
ALTER TABLE cd_jazz.personne ADD CONSTRAINT nommaj CHECK( initcap(nom_pers) = nom_pers );

INSERT INTO personne VALUES (DEFAULT, 'Potter', 'Chris', '01-01-1971', NULL, 1);
INSERT INTO edition VALUES (DEFAULT, 'ECM', 1);
INSERT INTO cd VALUES (DEFAULT, 'The sirens', (SELECT id_edition FROM edition WHERE nom_edition = 'ECM'), NULL, NULL, (SELECT id_pers FROM personne WHERE nom_pers = 'Potter' AND prenom_pers = 'Chris' AND date_nais = '01-01-1971'));

--Ajout d'un seul enregistrement
INSERT INTO enregistrement VALUES ((SELECT id_cd FROM cd WHERE titre_cd = 'The sirens'), 1, 'Wine Dark Sea', 8.47, '01-01-2013', NULL, NULL, (SELECT id_pers FROM personne WHERE nom_pers = 'Potter' AND prenom_pers = 'Chris' AND date_nais = '01-01-1971'));

INSERT INTO interprete VALUES ((SELECT id_cd FROM cd WHERE titre_cd = 'The sirens'), (SELECT id_enr FROM enregistrement WHERE id_cd = (SELECT id_cd FROM cd WHERE titre_cd = 'The sirens') AND titre_enr = 'Wine Dark Sea'), (SELECT id_pers FROM personne WHERE nom_pers = 'Potter' AND prenom_pers = 'Chris' AND date_nais = '01-01-1971'), 'saxophone');

*/
--Question 8

--CREATE SEQUENCE seqpers INCREMENT BY 5 START WITH 10;
--Modification des valeurs, demander

--Question 9

--CREATE OR REPLACE VIEW vuetp AS SELECT cd.id_cd, cd.titre_cd, cd.note_art, leadcd.nom_pers AS nom_leader , enregistrement.id_enr, enregistrement.titre_enr, enregistrement.annee_enr, persinter.nom_pers AS nom_interp, instrument, nomcomp.nom_pers FROM cd INNER JOIN leader ON cd.id_cd = leader.id_cd INNER JOIN personne AS leadcd ON leader.id_leader = leadcd.id_pers INNER JOIN enregistrement ON enregistrement.id_cd = cd.id_cd INNER JOIN interprete ON (enregistrement.id_cd, enregistrement.id_enr) = (interprete.id_cd, interprete.id_enr) INNER JOIN personne AS persinter ON id_interprete = persinter.id_pers INNER JOIN compositeur ON (compositeur.id_cd, compositeur.id_enr) = (enregistrement.id_cd, enregistrement.id_enr) INNER JOIN personne AS nomcomp ON id_compositeur = nomcomp.id_pers;

--Question 10

/*
CREATE OR REPLACE FUNCTION nbMorceauxArt(artiste varchar) RETURNS int AS $$

DECLARE

        mon_rec RECORD;
        
BEGIN

        SELECT * INTO mon_rec FROM interprete INNER JOIN personne ON id_pers = id_interprete WHERE nom_pers = artiste;
       
        IF NOT FOUND THEN
        
            RAISE EXCEPTION 'La personne % n existe pas', artiste;
            
        ELSE
        
        	RETURN (SELECT COUNT(*) FROM interprete INNER JOIN personne ON id_pers = id_interprete WHERE nom_pers = artiste);
        	
        END IF;
END;
	
$$ LANGUAGE plpgsql;

SELECT nbMorceauxArt('mikta');
SELECT nbMorceauxArt('mitta');
*/

--Question 11

/*

SELECT nom_interp AS "Musicien", age(MAX(annee_enr), MIN(annee_enr)) AS "Durée carrière" FROM vuetp GROUP BY nom_interp HAVING age(MAX(annee_enr), MIN(annee_enr)) >= ALL(SELECT age(MAX(annee_enr), MIN(annee_enr)) FROM vuetp GROUP BY nom_interp);

SELECT nom_interp AS "Musicien", COUNT(DISTINCT (id_cd, id_enr)) AS "Nombre enregistrements" FROM vuetp GROUP BY nom_interp HAVING COUNT(DISTINCT (id_cd, id_enr)) >= ALL(SELECT COUNT(DISTINCT (id_cd, id_enr)) FROM vuetp GROUP BY nom_interp);

SELECT vuetp.nom_interp AS "Musicien", COUNT(DISTINCT inter2.nom_interp) AS "Nombre de partenaires" FROM vuetp INNER JOIN vuetp AS inter2 ON (vuetp.id_cd, vuetp.id_enr) = (inter2.id_cd, inter2.id_enr) GROUP BY vuetp.nom_interp HAVING COUNT(DISTINCT inter2.nom_interp) >= ALL(SELECT COUNT(DISTINCT inter2.nom_interp) AS "Nombre de partenaires" FROM vuetp INNER JOIN vuetp AS inter2 ON (vuetp.id_cd, vuetp.id_enr) = (inter2.id_cd, inter2.id_enr) GROUP BY vuetp.nom_interp);

*/
