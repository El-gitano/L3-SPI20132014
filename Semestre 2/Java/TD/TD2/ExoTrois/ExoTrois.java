/**
* <h1>Class EtreHumain</h1>
*
* <p>
* Cette classe crée les bases de l'être humain qui:
*	<ul>
*		<li>A un âge</li>
*		<li>Vieillit</li>
*		<li>Se présente en donnant son âge</li>
*	</ul>
* </P>
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class EtreHumain
{
	/**
	* <p>
	* Nombre d'années qu'a vécu l'être humain.</br>
	* Augmente en vieillissant.
	* </p>
	*
	* @see EtreHumain#vieillir
	*/
	private int age;
	
	/** Constructeur initialisant l'âge à 0. */
	public EtreHumain()
	{
		age = 0;
	}
	
	/**
	* Permet d'avoir accès à la valeur de l'âge en dehors de la classe EtreHumain.
	*
	* @return int	Âge de l'être humain.
	*/
	public int getAge()
	{
		return age;
	}
	
	/**
	* Incrémente l'âge de l'être humain de une année.
	*
	* @see EtreHumain#age
	*/
	public void vieillir()
	{
		age++;
	}
	
	/**
	* Affiche la présentation de l'être humain, son âge compris.
	*
	* @return String	Affichage présentation être humain et l'âge de ce dernier.
	*/
	public String toString()
	{
		return "Je suis un être humain âgé de " + age + " année(s)";
	}
}

/**
* <h1>Class HommePolitique</h1>
* <p>
* Cette classe abstraite permet à un être humain d'être un homme politique et donc de débattre ainsi que d'ajouter des précisions à sa présentation.
* </p>
*
* @see EtreHumain
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
abstract class HommePolitique extends EtreHumain 
{
	/**
	* Classe abstraite étant redéfinie dans les classes héritées.
	*
	* @see Sarkozy#debattre
	* @see Hollande#debattre
	*/
	public abstract String debattre();
	
	/**
	* Affiche la présentation de l'être humain, ainsi que celle de l'homme politique.
	*
	* @see EtreHumain#toString
	*/
	public String toString()
	{
		return super.toString() + " et je peux débattre: \"" + debattre() + "\"";
	}
}

/**
* <h1>Class Chanteur</h1>
* <p>
* Cette classe abstraite permet à un être humain d'être un chanteur et donc de chanter ainsi que d'ajouter des précisions à sa présentation.
* </p>
*
* @see EtreHumain
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
abstract class Chanteur extends EtreHumain 
{
	/**
	* Classe abstraite étant redéfinie dans les classes héritées.
	*
	* @see Sanseverino#chanter
	* @see Shakira#chanter
	*/
	public abstract String chanter();
	
	/**
	* Affiche la présentation de l'être humain, ainsi que celle du chanteur.
	*
	* @see EtreHumain#toString
	*/
	public String toString()
	{
		return super.toString() + " et je peux chanter: \"" + chanter() + "\"";
	}
}

/**
* <h1>Class Sarkozy</h1>
* <p>
* Cette classe héritée de l'homme politique permet à un être humain d'être un Sarkozy et donc de débattre d'une certaine façon.
* </p>
*
* @see HommePolitique
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Sarkozy extends HommePolitique 
{
	/**
	* Affichage de l'orientation politique du débat.
	*
	* @return String	Texte de débat orienté à droite.
	*
	* @see HommePolitique#debattre
	*/
	public String debattre()
	{
		return "Blablabla de droite";
	}
}

/**
* <h1>Class Hollande</h1>
* <p>
* Cette classe héritée de l'homme politique permet à un être humain d'être un Hollande et donc de débattre d'une certaine façon.
* </p>
*
* @see HommePolitique
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Hollande extends HommePolitique
{
	/**
	* Affichage de l'orientation politique du débat.
	*
	* @return String	Texte de débat orienté à gauche.
	*
	* @see HommePolitique#debattre
	*/
	public String debattre()
	{
		return "Blablabla de gauche";
	}
}

/**
* <h1>Class Sanseverino</h1>
* <p>
* Cette classe héritée du chanteur permet à un être humain d'être un Sanseverino et donc de chanter certains airs.
* </p>
*
* @see Chanteur
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Sanseverino extends Chanteur 
{
	/**
	* Affichage de l'air chanté par le chanteur.
	*
	* @return String	Extrait d'un air de chanson de Sanseverino.
	*
	* @see Chanteur#chanter
	*/
	public String chanter()
	{
		return "La cigarette...";
	}
}

/**
* <h1>Class Shakira</h1>
* <p>
* Cette classe héritée du chanteur permet à un être humain d'être une Shakira et donc de chanter certains airs.
* </p>
*
* @see Chanteur
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Shakira extends Chanteur 
{
	/**
	* Affichage de l'air chanté par le chanteur.
	*
	* @return String	Extrait d'un air de chanson de Shakira.
	*
	* @see Chanteur#chanter
	*/
	public String chanter()
	{
		return "Bêêêêêê...";
	}
}

/**
* <h1>Class ExoTrois</h1>
* <p>
* Cette classe principale permet de tester les différentes classes créées en appelant des méthodes disponibles ou non pour chaque objet.
* </p>
*
* @see EtreHumain
* @see HommePolitique
* @see Chanteur
* @see Sarkozy
* @see Hollande
* @see Sanseverino
* @see Shakira
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
public class ExoTrois
{
	/** Méthode principale créant différents être humains afin de tester les méthodes qui leur sont disponibles */
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== ExoTrois ==================>\n");
		
		// Cas 1
		System.out.println("Création d'un Sanseverino: Sanseverino (qui prend une année)");
		Sanseverino s1 = new Sanseverino();
		s1.vieillir();
		System.out.println(s1.toString() + "\n");
	
		// Cas 2 ==> Faux
		System.out.println("Shakira m1 = new EtreHumain(); ==> Provoque une erreur, car un être humain n'est pas forcément une Shakira\n");
		//m1.vieillir();
	
		// Cas 3 ==> Faux
		System.out.println("Création d'un homme politique: Sarkozy");
		HommePolitique hp1 = new Sarkozy();
		System.out.println("System.out.println(hp1.toString()); ==> Provoque une erreur, car un homme politique ne peut pas chanter\n");
	
		// Cas 4 ==> Faux
		System.out.println("Création d'un être humain: Sanseverino");
		EtreHumain eh1 = new Sanseverino();
		System.out.println("System.out.println(eh1.toString()); ==> Provoque une erreur, car un être humain ne peut pas chanter\n");
	
		// Cas 5
		System.out.println("Création d'un être humain: Sanseverino");
		EtreHumain eh2 = new Sanseverino();
		System.out.println("Casting de l'être humain en chanteur");
		System.out.println(((Chanteur)eh2).toString() + "\n");
	
		// Cas 6 ==> Faux
		System.out.println("Création d'un être humain");
		EtreHumain eh3;
		System.out.println("Création d'un chanteur");
		Chanteur c1;
		System.out.println("Création d'une Shakira: Shakira");
		Shakira m2 = new Shakira();
		System.out.println("Création d'un Sanseverino: Sanseverino");
		Sanseverino s2 = new Sanseverino();
		System.out.println("==> Le chanteur vaut Shakira qui va chanter:");
		c1 = m2;
		System.out.println(c1.toString());
		System.out.println("==> Le chanteur vaut Sanseverino qui va chanter:");
		c1 = s2;
		System.out.println(c1.toString());
		System.out.println("==> L'être humain vaut le chanteur qui vaut Sanseverino");
		eh3 = c1;
		System.out.println("System.out.println(eh1.chanter()); ==> Provoque une erreur, car un être humain ne peut pas chanter. Il faudrait caster.");
		
		System.out.println("\n<==============================================>\n");
	}
}