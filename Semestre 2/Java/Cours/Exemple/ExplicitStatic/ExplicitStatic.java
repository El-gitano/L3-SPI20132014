// Javadoc ==> javadoc -private -charset "UTF-8" ExplicitStatic.java

/**
* <h3>Class Cup:</h3>
* 
* <p>
* Cette classe permet de créer et afficher un objet auquel on affilie un marqueur
* </p>
* 
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

class Cup
{	
	
	/**
	* Affichage de "Cup" et son marqueur à la déclaration
	*
	* @param marker
	*	marqueur de chaque Cup
	*/	
	Cup(int marker)
	{
		System.out.println("Initialisation Cup(" + marker + ")");
	}
	

	/**
	* Fonction affichant "f" et son marqeur
	*
	* @param marker
	*	marqueur de chaque Cup
	*
	* @see Cup#Cup
	*/
	void f(int marker)
	{
		System.out.println("Exécution f(" + marker + ")");
	}
}


/**
* <h3>Class Cups:</h3>
* 
* <p>
* Cette classe crée deux objets Cup et affiche son passage à l'écran
* </p>
* 
* @see Cup#Cup
* 
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

class Cups
{	
	/** Variable déclarée dès l'entrée dans la classe Cups */
	static Cup c2;
	/** Variable déclarée dès l'entrée dans la classe Cups */
	static Cup c3;
	
	// Puis immédiatement initialisées
	static
	{
		// Affichage de "Cup" et son marqueur
		c2 = new Cup(2);
		c3 = new Cup(3);
	}
	
	/** Le constructeur affiche simplement "Cups()" à la déclaration */
	Cups()
	{
		System.out.println("Initialisation Cups()");
	}
}


/**
* <h3>Class ExplicitStatic:</h3>
* 
* <p>
* Cette classe va nous permettre d'analyser l'ordre de déclaration des variables statiques, car elles sont mises en place avant même de rentrer dans la fonction principale.
* </p>
* 
* @see Cup#Cup
* @see Cups#Cups
* 
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

public class ExplicitStatic
{	
	/** Variable non statique et hors main ==> ignorée */
	Cup c5 = new Cup(5);
	/** Variable statique ==> dispo dans toute la classe ==> initialisée */
	static Cup c0 = new Cup(0);
	
	/** Fonction principale exécutée après les initialisations statiques */
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== Class ExplicitStatic ==================>\n");
		
		// Affichage rentrée dans main
		System.out.println("Inside main()");
		
		// Variable non statique, mais dans main ==> initialisée
		Cup c4 = new Cup(4);
		
		// Fonction effectuant le dernier affichage du programme
		Cups.c2.f(99);
		
		System.out.println("\n<==========================================================>\n");
	}
	
	// Variable non statique et hors main ==> ignorée
	Cup c6 = new Cup(6);
	// Variable statique ==> dispo dans toute la classe ==> initialisée avant le main
	static Cup c1 = new Cup(1);
	
	// Objet Cups initialisant deux Cup statiques supplémentaires c2 et c3
	static Cups x = new Cups();
	// Affiche seulement la déclaration d'un Cups ==> "Cups()"
	static Cups y = new Cups();
}
















