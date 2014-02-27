/**
 * Classe de test des classes Date, Auteur et Document
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 09:05:21 CET 2014
* @see Date
* @see Auteur
* @see Document
*/

public class Test {

	public static void main(String [] args){

		System.out.println("\n===== TEST CLASSE DATE =====\n");
		
		//Test de la levée d'exception Date
		try{

			Date date1 = new Date(10, 10, 2013);
			Date date2 = new Date(10, 13, 2014);
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}


		System.out.println("\n===== TEST COMPARAISON DATE =====\n");
		
		//Test comparaison Date
		try{

			Date date1 = new Date(10, 10, 2013);
			Date date2 = new Date(10, 12, 2014);
			
			System.out.println("date1 : " + date1);
			System.out.println("date2 : " + date2);
			System.out.println("Résultat de compareTo avec date1 et date2 (date1.compareTo(date2)) : " + date1.compareTo(date2));
		}
		catch(InvalidDateException e){
			
			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}


		System.out.println("\n===== TEST CLASSE AUTEUR =====\n");
		
		//Test levée d'exception auteur
		try{
			Auteur a1 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013), new Date(10, 12, 2012));
		}
		catch (InvalidAuteurException e){

			System.out.println(e.getMessage());
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}

	
		System.out.println("\n===== TEST COMPARAISON AUTEUR =====\n");
		
		//Test comparaison Auteur
		try{
			Auteur a1 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013), new Date(10, 12, 2014));
			Auteur a2 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013));
			Auteur a3 = new Auteur("Tremblain", "Rémi", new Date(10, 10, 2013), new Date(10, 12, 2014));
			Auteur a4 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013), new Date(10, 12, 2014));

			System.out.println("Test égalité a1 et a2 : " + a1.equals(a2));
			System.out.println("Test égalité a2 et a3 : " + a2.equals(a3));
			System.out.println("Test égalité a1 et a3 : " + a1.equals(a3));
			System.out.println("Test égalité a1 et a4 : " + a1.equals(a4));
			
		}
		catch (InvalidAuteurException e){

			System.out.println(e.getMessage());
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}
	
		System.out.println("\n===== TEST COMPARAISON DOCUMENT =====\n");
		
		//Test comparaison Documents
		try{
			Auteur a1 = new Auteur("Khomany", "Anice", new Date(10, 10, 2013), new Date(10, 12, 2014));
			Auteur a2 = new Auteur("Tremblain", "Rémi", new Date(10, 10, 2013), new Date(10, 12, 2014));
			
			Document d1 = new Document("Le titre", a1);
			Document d2 = new Document("Le titre", a2);
			Document d3 = new Document("Un autre titre", a1);
			Document d4 = new Document("Le titre", a1);

			System.out.println("Test égalité d1 et d2 : " + d1.equals(d2));
			System.out.println("Test égalité d1 et d3 : " + d1.equals(d3));
			System.out.println("Test égalité d1 et d4 : " + d1.equals(d4));
			System.out.println("Test égalité d2 et d3 : " + d2.equals(d3));
		}
		catch (InvalidAuteurException e){

			System.out.println(e.getMessage());
		}
		catch (InvalidDateException e){

			System.out.println("Erreur dans la déclaration d'un objet Date : " + e.getMessage() );
		}

		TestBase.Test();
	}
}