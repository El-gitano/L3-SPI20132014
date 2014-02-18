/**
 * Classe de test de la classe BaseDocuments
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 19:06:08 CET 2014
* @see BaseDocuments
*/

import java.util.*;

public class TestBase {

	/** Teste les différentes méthodes de la classe BaseDocuments
	 *  @see BaseDocuments
	 */
	public static void Test(){

		//Test BaseDocuments
		try{
			BaseDocuments bd = new BaseDocuments("Ma première base");

			//Déclaration des auteurs
			Auteur a1 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013), new Date(10, 12, 2014));
			Auteur a2 = new Auteur("Tremblain", "Rémi", new Date(10, 10, 2013), new Date(10, 12, 2014));

			//Déclaration des documents
			Document d1 = new Document("Le titre", a1);
			Document d2 = new Document("Le titre", a2);
			Document d3 = new Document("Un autre titre", a1);
			Document d4 = new Document("Le titre", a1);
			Document d5 = new Document("Le titre qui n'est pas dans la bdd", a1);

			//Ajouts des documents
			bd.ajoute(d1);
			bd.ajoute(d2);
			bd.ajoute(d3);
			bd.ajoute(d4);

			bd.affiche();

			//Supression
			bd.supprime(d4);

			bd.affiche();

			//Test levée d'exception disponibilité
			try{

				bd.estDisponible(d5);
			}
			catch (NoSuchElementException e){

				System.out.println(e.getMessage());
			}

			//Test emprunt/remise
			try{

				System.out.println(bd.estDisponible(d4));
				bd.emprunte(d4);
				System.out.println(bd.estDisponible(d4));
				bd.rend(d4);
				System.out.println(bd.estDisponible(d4));
			}
			catch (NoSuchElementException e){

				System.out.println(e.getMessage());
			}

			//Levée d'exception emprunt
			try{

				bd.emprunte(d5);
			}
			catch (NoSuchElementException e){

				System.out.println(e.getMessage());
			}
		}
		catch (InvalidAuteurException e){

			System.out.println(e.getMessage());
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}
	}
}