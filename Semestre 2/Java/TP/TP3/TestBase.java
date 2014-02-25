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

		System.out.println("\n===== TEST BASE DOCUMENTS =====\n");
		
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

			System.out.println("\n===== TEST SELECTIONNEURS =====\n");
			
			//Déclaration des selectionneurs
			NonEmprunteSelectionneur nonEmpSelect = new NonEmprunteSelectionneur();
			AuteurVivantSelectionneur autVivSelect = new AuteurVivantSelectionneur(new Date(01, 01, 2005));
			MotDansTitreSelectionneur motTitSelect = new MotDansTitreSelectionneur("polymorphisme");
			
			SelectionneurComposite comSelect = new SelectionneurComposite();
			comSelect.add(autVivSelect);
			comSelect.add(motTitSelect);
			comSelect.add(motTitSelect);

			Auteur a3 = new Auteur("Khomany", "Anice", new Date(10, 10, 2003), new Date(10, 12, 2004));
			Auteur a4 = new Auteur("Tremblain", "Rémi", new Date(10, 10, 2010), new Date(10, 12, 2013));

			//Déclaration des documents
			Document d6 = new Document("Le polymorphisme", a3);
			Document d7 = new Document("La tourte", a4);
			
			Document d8 = new Document("Un autre titre", a4);
			d8.setEmprunt(true);

			//Test des selectionneurs

			//Emprunt
			System.out.println(nonEmpSelect.estSatisfaitPar(d6));
			System.out.println(nonEmpSelect.estSatisfaitPar(d8));

			//Auteur vivant à une date donnée
			System.out.println(autVivSelect.estSatisfaitPar(d6));
			System.out.println(autVivSelect.estSatisfaitPar(d7));

			//Mot dans le titre
			System.out.println(motTitSelect.estSatisfaitPar(d6));
			System.out.println(motTitSelect.estSatisfaitPar(d7));	

			//Test sélectionneur composite
			System.out.println(comSelect.estSatisfaitPar(d6));
			System.out.println(comSelect.estSatisfaitPar(d7));
			System.out.println(comSelect.estSatisfaitPar(d8));


			//Test tri bdDoc
			System.out.println("\n===== TEST TRI =====\n");

			//Ajout des documents précédents + nouveaux documents pour la comparaison
			bd.ajoute(d6);
			bd.ajoute(d7);
			bd.ajoute(d8);

			Document d9 = new Document("Le polymorphisme en Angleterre", a3);
			Document d10 = new Document("Le polymorphisme Java", a3);
			Document d11 = new Document("Le polymorphisme Python", a3);

			bd.ajoute(d9);
			bd.ajoute(d10);
			bd.ajoute(d11);

			//Affiche de la liste résultat
			Iterator itTri = bd.listeTriee(bd.selectionne(motTitSelect), new TitreComparator()).iterator();

			while (itTri.hasNext()){

				System.out.println((Document)itTri.next());
			}

			System.out.println("\n===== FIN TESTS =====\n");
		}
		catch (InvalidAuteurException e){

			System.out.println(e.getMessage());
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}
	}
}