--Question 1

--SELECT * FROM enregistrement ORDER BY annee_enr;

--Question 2

--SELECT COUNT(DISTINCT instrument) AS "Nombre d'instruments" FROM interprete;

--Question 3

--SELECT date_deces AS "Mort depuis + de 10 ans" FROM personne WHERE age(date_deces) < INTERVAL '10 years';

--Question 4

--SELECT * FROM enregistrement WHERE cond_enr = 'public' AND lieu_enr IN ('chicago', 'saint-louis');

--Question 5

--SELECT titre_cd, nom_pers AS "nom du leader" FROM cd INNER JOIN leader ON leader.id_cd = cd.id_cd INNER JOIN personne ON personne.id_pers = leader.id_leader WHERE nom_pers LIKE '%o%';

--Question 6

--SELECT DISTINCT instrument FROM enregistrement INNER JOIN interprete ON (interprete.id_cd, interprete.id_enr) = (enregistrement.id_cd, enregistrement.id_enr) WHERE annee_enr BETWEEN date '1980-01-01' AND date '1990-01-01';

--Question 7

--SELECT id_cd FROM enregistrement WHERE duree_enr = (SELECT MAX(duree_enr) FROM enregistrement WHERE cond_enr IN ('public', 'acoustic')) AND cond_enr IN ('public', 'acoustic');

--Question 8

--SELECT cd.id_cd AS "ID du cd", titre_cd AS "Titre du CD", SUM(duree_enr) AS "Durée du cd" FROM cd INNER JOIN enregistrement ON cd.id_cd = enregistrement.id_cd GROUP BY cd.id_cd ORDER BY cd.id_cd ASC;

--Question 9

--SELECT nom_pers, prenom_pers, annee_enr FROM interprete INNER JOIN enregistrement ON (enregistrement.id_cd, enregistrement.id_enr) = (interprete.id_cd, interprete.id_enr) INNER JOIN personne ON id_pers = id_interprete WHERE instrument = 'bandoneon' AND annee_enr <= ALL(SELECT annee_enr FROM interprete INNER JOIN enregistrement ON (enregistrement.id_cd, enregistrement.id_enr) = (interprete.id_cd, interprete.id_enr) WHERE instrument = 'bandoneon');

--Question 10

--SELECT nom_pers, prenom_pers FROM enregistrement INNER JOIN interprete ON (enregistrement.id_cd, enregistrement.id_enr) = (interprete.id_cd, interprete.id_enr) INNER JOIN personne ON personne.id_pers = interprete.id_interprete WHERE enregistrement.id_cd IN (SELECT id_cd FROM leader INNER JOIN personne ON id_leader = id_pers WHERE nom_pers = 'coltrane') AND (interprete.id_cd, interprete.id_enr) IN (SELECT id_cd, id_enr FROM interprete WHERE instrument = 'bass');

--Question 11

--SELECT id_cd FROM enregistrement GROUP BY id_cd HAVING COUNT(*) <= ALL (SELECT COUNT(*) FROM enregistrement GROUP BY id_cd);

--Question 12

--SELECT id_cd AS "CD avec le max d'interprètes" FROM interprete GROUP BY id_cd HAVING COUNT(DISTINCT id_interprete) >= ALL(SELECT COUNT(DISTINCT id_interprete) FROM interprete GROUP BY id_cd);

--Question 13

--SELECT nom_pers AS "Nom", prenom_pers AS "Prénom", age(MAX(annee_enr), MIN(annee_enr)) AS "Durée de carrière" FROM interprete INNER JOIN enregistrement ON (interprete.id_cd, interprete.id_enr) = (enregistrement.id_cd, enregistrement.id_enr) INNER JOIN personne ON id_pers = id_interprete GROUP BY id_pers HAVING age(MAX(annee_enr), MIN(annee_enr)) >= ALL (SELECT age(MAX(annee_enr), MIN(annee_enr)) FROM interprete INNER JOIN enregistrement ON (interprete.id_cd, interprete.id_enr) = (enregistrement.id_cd, enregistrement.id_enr) GROUP BY id_interprete);

--Question 14

--SELECT nom_pers AS "Nom", prenom_pers AS "Prénom" FROM personne INNER JOIN interprete ON id_interprete = id_pers GROUP BY id_pers HAVING COUNT(DISTINCT (id_cd, id_enr)) >= ALL(SELECT COUNT(DISTINCT (id_cd, id_enr)) FROM interprete GROUP BY id_interprete);

--Question 15

--SELECT nom_pers AS "Nom", prenom_pers AS "Prénom" FROM personne INNER JOIN interprete AS inter ON id_interprete = id_pers INNER JOIN interprete AS inter2 ON (inter.id_cd, inter.id_enr) = (inter2.id_cd, inter2.id_enr) GROUP BY id_pers HAVING COUNT(DISTINCT inter2.id_interprete) >= ALL(SELECT COUNT(DISTINCT inter2.id_interprete) FROM interprete AS inter INNER JOIN interprete AS inter2 ON (inter.id_cd, inter.id_enr) = (inter2.id_cd, inter2.id_enr)  GROUP BY inter.id_interprete);
