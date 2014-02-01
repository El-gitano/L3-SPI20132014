// Javadoc ==> javadoc -private -charset "UTF-8" Flower.java

/**
* <h1>Class Flower</h1>
* <h2>permettant de créer des fleurs en initialisant:</h2>
* <p>
* <i>- Soit un nombre de pétales</br>
* - Soit un libellé</br>
* - Soit les deux</br>
* - Soit rien</br></i>
* </p>
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

public class Flower
{
	/** Variable contenant le nombre de pétales de la fleur */
	private int petalCount = 0;
	/** Variable contenant le nom de la fleur */
	private String flowerName = new String("null");
	
	/**
	* Création d'une fleur avec un nombre de pétales.
	*
	* @param petals Nombre de pétales qui appartiendront à la fleur.
	*/
	Flower(int petals)
	{
		petalCount = petals;
		
		System.out.println("Constructor with number of petals = " + petalCount);
	}
	
	/**
	* Création d'une fleur avec un nom.
	*
	* @param name Nom de la fleur.
	*/
	Flower(String name)
	{
		flowerName = name;
		
		System.out.println("Constructor with flower's name = " + flowerName);
	}
	
	/**
	* Construction d'une fleur avec un nombre de pétales et un nom.
	*
	* @param petals Nombre de pétales qui appartiendront à la fleur.
	* @param name Nom de la fleur.
	*/
	Flower(int petals, String name)
	{
		petalCount = petals;
		flowerName = name;
		
		System.out.println("Constructor with number of petals = " + petalCount + " and flower's name = " + flowerName);
	}
	
	/** Construction d'une fleur sans spécifications */
	Flower()
	{
		// Initialisation par défaut
		petalCount = 42;
		flowerName = "Rose des sables";
		
		System.out.println("Constructor with default number of petals = " + petalCount + " and flower's name = " + flowerName);
	}
	
	/**
	* Fonction principale créant quatre types de fleur.
	*
	* @see Flower#Flower(int)
	* @see Flower#Flower(String)
	* @see Flower#Flower(int, String)
	* @see Flower#Flower()
	*/
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== Class Flower ==================>\n");
		
		Flower maFleur1 = new Flower(69);
		Flower maFleur2 = new Flower("Coquelicot");
		Flower maFleur3 = new Flower(10, "Tulipe");
		Flower maFleur4 = new Flower();
		
		System.out.println("\n<===================================================>\n");
		
		System.exit(0);
	}
}












