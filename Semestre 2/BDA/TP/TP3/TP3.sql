--Préalable
/*DROP LANGUAGE plpgsql CASCADE;
--CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler VALIDATOR plpgsql_validator;*/

--Question 1

/*CREATE OR REPLACE FUNCTION hello() RETURNS void AS $$

BEGIN
	
	RAISE NOTICE 'Hello World !';
END;
	
$$ LANGUAGE plpgsql;

SELECT hello();*/

--Question 2

/*CREATE OR REPLACE FUNCTION bonjour(Nom varchar(60)) RETURNS varchar(60) AS $$

DECLARE
	
	res varchar(60);
	
BEGIN
	
	res:= 'Bonjour ' || initcap(lower(Nom));
	RETURN res;

END;
	
$$ LANGUAGE plpgsql;

SELECT bonjour('Antoine');
SELECT bonjour('anice');*/

--Question 3

/*CREATE OR REPLACE FUNCTION maxmin(nb1 int, nb2 int) RETURNS RECORD AS $$

DECLARE
	
	res RECORD;
	
BEGIN
	
	RAISE NOTICE 'a vaut %', nb1;
	RAISE NOTICE 'b vaut %', nb2;
	
	IF nb1 = nb2 THEN
	
		SELECT nb1 INTO res;
	ELSE
	
		IF nb1 > nb2 THEN
		
			SELECT nb1, nb2 INTO res;
			
		ELSE
		
			SELECT nb2, nb1 INTO res;
			
		END IF;
	END IF;
	
	RETURN res;
END;
	
$$ LANGUAGE plpgsql;

SELECT * FROM maxmin(1, 1) AS tmp (equals integer);
SELECT * FROM maxmin(1, 3) AS tmp (max integer, min integer);
SELECT maxmin(3, 1) AS tmp (max integer, min integer);*/

--Question 4

/*CREATE OR REPLACE FUNCTION factorec(nb int) RETURNS int AS $$
	
BEGIN
	
	IF nb < 1 THEN
	
		RAISE EXCEPTION 'Le nombre % ne peut pas être utilisé dans factorielle !', nb;
		
	END IF;
	
	IF nb = 1 THEN
	
		RETURN 1;
	
	ELSE
	
		RETURN nb * factoRec(nb-1);
		
	END IF;

END;
	
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION factoiter(nb int) RETURNS int AS $$

DECLARE 

	res int;
	cpt int;
	
BEGIN
	
	IF nb < 1 THEN
	
		RAISE EXCEPTION 'Le nombre % ne peut pas être utilisé dans factorielle !', nb;
		
	END IF;
	
	res := 1;
	cpt := nb;
	
	WHILE cpt > 1
	LOOP
	
		res := (res*cpt);
		cpt := (cpt-1);
		
	END LOOP;
	
	RETURN res;
	
END;
	
$$ LANGUAGE plpgsql;


SELECT factoRec(-1);
SELECT factoRec(3);
SELECT factoRec(4);

SELECT factoiter(-1);
SELECT factoiter(3);
SELECT factoiter(4);*/

--Question 5

/*
CREATE OR REPLACE FUNCTION tablemul(nb int) RETURNS SETOF RECORD AS $$

DECLARE 

	res RECORD;
	cpt int;
	
BEGIN
	
	cpt := 0;
	
	FOR cpt IN 0..11
	
		SELECT cpt, nb, (cpt*nb) INTO res;
		cpt := (cpt+1);
		RETURN NEXT res;
	END LOOP;
	
	RETURN;
	
END;

$$ LANGUAGE plpgsql;

SELECT * FROM tablemul(-1) AS mult(a int, b int, mul int);
SELECT * FROM tablemul(4) AS mult(a int, b int, mul int);
*/

--Question 6

/*
CREATE OR REPLACE FUNCTION nbinstruments(nom varchar(60), prenom varchar(60)) RETURNS int AS $$

DECLARE 

	mon_rec record;
		
BEGIN
	
	SELECT * INTO mon_rec FROM interprete INNER JOIN personne ON personne.id_pers = interprete.id_interprete WHERE personne.nom_pers = nom AND personne.prenom_pers = prenom;
	
	IF NOT FOUND THEN
	
		RAISE EXCEPTION 'La personne % % n existe pas dans la bdd', nom, prenom;
	
	ELSE
	
        RETURN (SELECT COUNT(*) FROM interprete INNER JOIN personne ON personne.id_pers = interprete.id_interprete WHERE personne.nom_pers = nom AND personne.prenom_pers = prenom);	
        
	END IF;
END;

$$ LANGUAGE plpgsql;

SELECT nbinstruments('mikta', 'boris');
SELECT nbinstruments('mikt', 'boris');
*/

--Question 7

/*
CREATE OR REPLACE FUNCTION testquery(query varchar) RETURNS void AS $$
	
BEGIN
	
	EXECUTE query;
	RAISE NOTICE 'Requête syntaxiquement correcte';

EXCEPTION

	WHEN UNDEFINED_COLUMN THEN
	
		RAISE EXCEPTION 'Une colonne de la requête n\'existe pas';
		
	WHEN UNDEFINED_TABLE THEN
	
		RAISE EXCEPTION 'Une table de la requête n\'existe pas';
END;

$$ LANGUAGE plpgsql;

SELECT testquery('SELECT * FROM personne;');
SELECT testquery('SELECT * FROM persone;');
SELECT testquery('SELECT npers FROM personne;');*/
