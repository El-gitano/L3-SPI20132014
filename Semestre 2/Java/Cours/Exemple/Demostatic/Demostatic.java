// Javadoc ==> javadoc -private -charset "UTF-8" Demostatic.java

/**
* <h1>Class Partageuse</h1>
* <p>
* Cette classe permet d'initialiser et modifier des variables static et non-static
* </p>	
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

class Partageuse
{
	/** (Statique) Elle est partagée dans toute la classe */
	static int partage = 2;
	/** (Non-statique) Elle n'est modifiable que dans la classe qui l'a créé */
	int nonPartage = 2;
	
	/** Fonction mofifiant la variable statique et la non-statique */
	void modifie()
	{
		partage = 3;
		nonPartage = 3;
	}
}


/**
* <h1>Class Demostatic</h1>
* <p>
* Cette classe permet de montrer l'utilité des variables statiques
* </p>
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 29 2014
*/

public class Demostatic
{
	/**
	* <p>
	* Fonction principale créant deux objets Partageuse.</br>
	* Modifiant le premier</br>
	* Puis affichant à nouveau ces deux objets pour voir que le deuxième a également été modifié
	* </p>
	*
	* @see Partageuse
	* @see Partageuse#modifie
	*/
	static public void main(String[] args)
	{
		System.out.println("\n\n<================== Class Demostatic ==================>\n");
		
		Partageuse p1 = new Partageuse();
		Partageuse p2 = new Partageuse();
		
		System.out.println("Les deux objets de partage ont été créés et initialisés à 2\n");
		
		// Affichage des variables des objets créés
		System.out.println("p1: partagé = " + p1.partage + ", non partagée = " + p1.nonPartage);
		System.out.println("p2: partagé = " + p2.partage + ", non partagée = " + p2.nonPartage + "\n");
		
		// On modifie les deux variables du premier objet
		p1.modifie();
		
		System.out.println("Nous avons modifié le premier objet p1 en passant ses variables à 3\n");
		
		// La variable statique du second objet a aussi été modifiée
		System.out.println("p1: partagé = " + p1.partage + ", non partagée = " + p1.nonPartage);
		System.out.println("p2: partagé = " + p2.partage + ", non partagée = " + p2.nonPartage + "\n");
		
		System.out.println("La variable partage, qui est statique, a donc été modifiée dans tous les objets.\nSeul la variable non partagée du deuxième objet p2 n'a pas été modifiée.");
		
		System.out.println("\n<======================================================>\n");
	}
}
