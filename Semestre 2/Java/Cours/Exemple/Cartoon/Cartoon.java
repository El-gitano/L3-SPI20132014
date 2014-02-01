// Javadoc ==> javadoc -private -charset "UTF-8" Cartoon.java

/**
* <h1>Class Art</h1>
* 
* <p>
* Cette classe permet de construire un "Art".
* </p>
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 28 2014
*/

class Art
{
	/** Constructeur affichant uniquement "Art constructor" à la déclaration */
	Art()
	{
		System.out.println("Art constructor");
	}
}


/**
* <h1>Class Drawing</h1>
* 
* <p>
* Cette classe permet de construire un "Dessin".</br>
* Elle hérite de "Art".
* </p>
*
* @see Art
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 28 2014
*/

class Drawing extends Art
{
	/** Constructeur affichant uniquement "Drawing Constructor" à la déclaration */
	Drawing()
	{
		System.out.println("Drawing constructor");
	}
}


/**
* <h1>Class Cartoon</h1>
* 
* <p>
* Cette classe permet de construire un "Cartoon".</br>
* Elle hérite de "Drawing".
* </p>
*
* @see Drawing
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 28 2014
*/

class Cartoon extends Drawing
{
	/** Constructeur affichant uniquement "Cartoon Constructor" à la déclaration */
	Cartoon()
	{
		System.out.println("Cartoon constructor");
	}

	/** Fonction principale qui va créer un objet appartenant à plusieurs classes héritées */
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== Class Cartoon ==================>\n");
		
		/*
		* Crée un objet Cartoon qui est un Dessin, qui est lui-même un Art.
		* On a ici un objet qui appartient aux trois classes et qui va donc les utiliser les unes après les autres.
		*/
		Cartoon x = new Cartoon();
		
		System.out.println("\n<===================================================>\n");
	}
}