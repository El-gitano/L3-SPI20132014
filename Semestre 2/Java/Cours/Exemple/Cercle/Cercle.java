// Javadoc ==> javadoc -private -charset "UTF-8" Cercle.java

/** 
* <h3>Class Cercle</h3>
*
* <p>
* Cette classe nous permet de créer un cercle</br>
* Ainsi que de trouver le cercle le plus grand
* </p>
*
* @author Anice Khomany
* @version 0.1 : Date : Wed Jan 28 2014
*/
	
public class Cercle
{
	/** Variable représentant le rayon du cercle */
	public double r;
	
	/**
	* <p>
	* Constructeur de cercle</br>
	* Affiche la valeur du rayon à la déclaration
	* </p>
	*
	* @param r
	*	Rayon du cercle créé
	*/
	public Cercle(double r)
	{
		System.out.println("Valeur de \"this.r\" = " + this.r);
		System.out.println("Valeur de \"r\" = " + r);
		
		this.r = r;
	}
	
	/**
	* <p>
	* Méthode affichant la rayon des deux cercles et retournant le plus grand cercle
	* </p>
	*
	* @param c
	*	Cercle à comparer à celui juxtaposé devant la méthode
	*
	* @return Le cercle au plus grand rayon
	*
	* @see Cercle#Cercle
	*/
	public Cercle plusGrand(Cercle c)
	{
		// Affichage rayon cercle en paramètre
		System.out.println("Valeur de \"c.r\" = " + c.r);
		
		// Affichage rayon cercle devant méthode (2 façons)
		System.out.println("Valeur de \"r\" = " + r);
		System.out.println("Valeur de \"this.r\" = " + this.r);
		
		// Si rayon cercle en paramètre plus grand
		if(c.r > r)
			// On le renvoie
			return c;
		else
			// Sinon on renvoie celui devant la méthode
			return this;
	}
	
	/** Fonction principale créant deux cercles, les comparant, puis affichant le rayon du plus grand. */
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== Class Cercle ==================>\n");
		
		// Création de deux cercles
		Cercle monCercle = new Cercle(3);
		Cercle monSecondCercle = new Cercle(10);
		
		// Comparaison de ces deux cercles
		Cercle monPlusGrandCercle = monCercle.plusGrand(monSecondCercle);
		
		// Affichage du rayon du plus grand
		System.out.println("Mon plus grand cercle a un rayon de " + monPlusGrandCercle.r);
		
		System.out.println("\n<==================================================>\n");
		
		System.exit(0);
	}
}