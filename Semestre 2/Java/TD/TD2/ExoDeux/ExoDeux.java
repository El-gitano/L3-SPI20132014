/**
* <h1>Class Mother</h1>
* Classe mère qui sera héritée
*/
class Mother
{
	/**
	* <p>
	* Méthode affichant la méthode appelée ==> Ici la méthode de la classe Mother.
	* </P>
	*
	* @param m	Permet d'appeler la méthode "methode" à l'aide d'un objet de type Mother
	*/
	public void methode(Mother m)
	{
		System.out.println("methode(Mother m) appelée");
	}
}

/**
* <h1>Class Daughter</h1>
* Classe fille qui hérite de la classe mère
*
* @see Mother
*/
class Daughter extends Mother
{
	/**
	* <p>
	* Méthode affichant la méthode appelée ==> Ici la méthode de la classe Daughter.
	* </P>
	*
	* @param d	Redéfinition permettant d'appeler la méthode "methode" à l'aide d'un objet de type Daughter
	*
	* @see Mother#methode
	*/
	public void methode(Daughter d)
	{
		System.out.println("methode(Daughter m) appelée");
	}
}

/**
* <h1>Class ExoDeux</h1>
* Classe principale qui explique le mécanisme d'héritage
*
* @see Mother
* @see Daughter
*/
public class ExoDeux
{
	/**
	* Méthode créant et testant des objets de type Mother et Daughter
	*
	* @see Mother
	* @see Daughter
	*/
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== ExoDeux ==================>\n");
		
		/** Premier objet de type mother pour les tests*/
		Mother m1 = new Mother();
		/** Deuxième objet de type mother pour les tests*/
		Mother m2 = new Mother();
		
		/** Premier objet de type daughter pour les tests*/
		Daughter d1 = new Daughter();
		/** Deuxième objet de type daughter pour les tests*/
		Daughter d2 = new Daughter();
		
		m1.methode(m2);
		m1.methode(m1);
		
		// Considère d1 comme un objet de class Mere
		m1.methode(d1);
		
		d1.methode(m1);
		d1.methode(d2);
		
		System.out.println("\n<==============================================>\n");
	}
}