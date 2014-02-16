/**
* <h1>Class Joueur</h1>
*
* <p>
* Chaque joueur possède un numéro qui l'identifie, une stratégie et une position.</br>
* Une stratégie durant de 2 à 5 tours est descernée aléatoirement à chaque joueur.</br>
* Un joueur se déplace selon la stratégie qu'il utilise à ce moment précis.</br>
* Un joueur gagne lorsqu'il atteint ou dépasse la position 500.
* </p>
*
* @see Strategie
* @see Jeux#affecteUneStrategieAleatoire
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Joueur
{
	/**
	* Contient la position courante du joueur.</br>
	* Détermine si le joueur est gagnant ou non.</br>
	*
	* @see Joueur#gagnant
	* @see Joueur#deplace
	*/
	private int position;
	
	/** Identifiant du joueur. */
	private int numeroDeJoueur;
	
	/**
	* Stratégie actuelle du joueur. </br>
	*
	* @see Joueur#affecteStrategie
	* @see Strategie
	*/
	private Strategie str;
	
	/**
	* Durée pendant la stratégie actuelle va être active.</br>
	*
	* @see Joueur#affecteStrategie
	*/
	private int dureeStrategie;
	
	/** Permet d'obtenir des nombres aléatoires. */
	private java.util.Random rnd;
	
	/**
	* Création d'un joueur à l'aide d'un numéro.
	*
	* @param num	Numéro qui sera attribué au joueur comme son identifiant.
	* @param random	Permet de générer un nombre aléatoire différent pour chaque joueur. 
	*/
	public Joueur(int num, java.util.Random random)
	{
		numeroDeJoueur = num;
		rnd = random;
		position = 0;
		
	}
	
	/**
	* Teste si le joueur est gagnant ==> position supérieure ou égale à 500.
	*
	* @return boolean	True si le joueur est gagnant, false sinon.
	*/
	public boolean gagnant()
	{
		return(position >= 500);
	}
	
	/**
	* Déplace le joueur selon la distance donnée en paramètre et sa stratégie.
	*
	* @param distance	Distance utilisée pour le déplacement du joueur.
	*/
	public void deplace(int distance)
	{
		dureeStrategie--;
		
		position += str.changePosition(distance);
	}
	
	/**
	* Décerne une stratégie à un joueur de manière aléatoire avec une durée aléatoire.
	*
	* @param strategie	Stratégie actuelle à modifier.
	*/
	public void affecteStrategie(Strategie strategie)
	{
		str = strategie;
		// Durée aléatoire entre 2 et 5
		dureeStrategie = 2 + rnd.nextInt(4);
			
		System.out.println("\nLa stratégie du joueur " + numeroDeJoueur + " est " + str.affiche() + ". Elle durera " + dureeStrategie() + " tours.\n");
	}
	
	/**
	* Donne la durée de la stratégie, même en dehors de la classe.
	*
	* @return int	Durée restante de la stratégie.
	*/
	public int dureeStrategie()
	{
		return dureeStrategie;
	}
	
	/**
	* Donne la position actuelle du joueur, même en dehors de la classe.
	*
	* @return int	Position actuelle du joueur.
	*/
	public int position()
	{
		return position;
	}
	
	/**
	* Donne le numéro du joueur, même en dehors de la classe.
	*
	* @return int	Numéro identifiant le joueur.
	*/
	public int numero()
	{
		return numeroDeJoueur;
	}
}


/**
* <h1>Class Stratégie</h1>
*
* <p>
* Cette classe abstraite permet de créer trois stratégies distinctes qui permettront au joueur
* de se déplacer de trois manières différentes.
* </p>
*
* @see Strategie1
* @see Strategie2
* @see Strategie3
* @see Jeux#affecteUneStrategieAleatoire
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
abstract class Strategie
{
	/**
	* Tableau des joueurs.
	*
	* @see Joueur#Joueur
	*/
	protected Joueur[] joueur;
	
	/**
	* Nombre de joueurs.
	*
	* @see Joueur#Joueur
	*/
	protected int nombreDeJoueur;
	
	/**
	* Numéro du joueur.
	*
	* @see Joueur#Joueur
	*/
	protected int numeroDeJoueur;
	
	/**
	* Base du constructeur de Stratégie.
	*
	* @param j	Tableau de joueur sur lequel effectuer les actions.
	* @param nbJoueurs	Nombre de joueurs à prendre en compte dans le tableau de joueurs.
	* @param numJoueur	Numéro du joueur auquel il faudra affecter une stratégie.
	*/
	public Strategie(Joueur[] j, int nbJoueurs, int numJoueur)
	{
		joueur = j;
		nombreDeJoueur = nbJoueurs;
		numeroDeJoueur = numJoueur;
	}
	
	/**
	* Permet au joueur de se déplacer selon la stratégie adoptée.
	*
	* @param d	Distance à prendre en compte dans les calculs de déplacement.
	*/
	abstract int changePosition(int d);
	
	/**
	* Affiche la Stratégie adoptée.
	*
	* @return String	Retourne la chaine "La stratégie de type ???".
	*/
	String affiche()
	{
		return "la stratégie de type ";
	}
}


/**
* <h1>Class Stratégie 1</h1>
*
* <p>
* Cette classe permet au joueur de se déplacer à l'aide du calcul suivant :</br>
* <ul>
*		<li>Valeur du dé + (position du premier - position du joueur) / 2</li>
*		<li>Si le dé a pour valeur 3, 4, 5 ou 6 le déplacement est positif, sinon il est négatif</li>
* </ul>
* </p>
*
* @see Strategie
* @see Jeux#affecteUneStrategieAleatoire
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Strategie1 extends Strategie
{
	/**
	* Constructeur de la Stratégie 1 identique à celui de la classe mère.
	*
	* @param j	Tableau de joueur sur lequel effectuer les actions.
	* @param nbJoueurs	Nombre de joueurs à prendre en compte dans le tableau de joueurs.
	* @param numJoueur	Numéro du joueur auquel il faudra affecter une stratégie.
	*/
	public Strategie1(Joueur[] j, int nb, int num)
	{
		super(j, nb, num);
	}
	
	/**
	* Permet au joueur de se déplacer d'une distance égale à la valeur du dé + (position du premier - position du joueur) / 2.</br>
	* De plus, si le dé a pour valeur 3, 4, 5 ou 6 le déplacement est positif, sinon il est négatif.
	*                                            
	* @param d	Distance à prendre en compte dans les calculs de déplacement.
	*/
	public int changePosition(int d)
	{
		/** Contient la position du joueur en première position.*/
		int highest = joueur[numeroDeJoueur].position();
		
		// Obtention de la position du joueur en première position
		for(int i = 2 ; i < nombreDeJoueur ; i++)
		{
			if(joueur[i].position() > highest)
				highest = joueur[i].position();
		}
		
		/** Contient le résultat du calcul donnant la distance absolue que le joueur va parcourir.*/
		int change = d + (highest - joueur[numeroDeJoueur].position()) / 2;
		
		return(d > 2) ? change : -change;
	}
	
	/**
	* Annonce que la stratégie adoptée est la numéro 1.
	*
	* @return String	Retourne la chaine "La stratégie de type 1".
	*/
	public String affiche()
	{
		return super.affiche() + "1";
	}
}

/**
* <h1>Class Stratégie 2</h1>
*
* <p>
* Cette classe permet au joueur de se déplacer à l'aide du calcul suivant :</br>
* <ul>
*		<li>3 fois la valeur du dé si cette valeur est paire, une fois la valeur du dé si celle-ci est impaire.</li>
*		<li>Ce changement de position est toujours positif.</li>
* </ul>
* </p>
*
* @see Strategie
* @see Jeux#affecteUneStrategieAleatoire
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Strategie2 extends Strategie
{
	/**
	* Constructeur de la Stratégie 2 identique à celui de la classe mère.
	*
	* @param j	Tableau de joueur sur lequel effectuer les actions.
	* @param nbJoueurs	Nombre de joueurs à prendre en compte dans le tableau de joueurs.
	* @param numJoueur	Numéro du joueur auquel il faudra affecter une stratégie.
	*/
	public Strategie2(Joueur[] j, int nb, int num)
	{
		super(j, nb, num);
	}
	
	/**
	* Permet au joueur de se déplacer d'une distance égale à 3 fois la valeur du dé si cette valeur est paire, une fois la valeur du dé si celle-ci est impaire.</br>
	* Ce changement de position est toujours positif.
	*                                            
	* @param d	Distance à prendre en compte dans les calculs de déplacement.
	*/
	public int changePosition(int d)
	{
		return(d % 2 == 0) ? (3 * d) : d;
	}
	
	/**
	* Annonce que la stratégie adoptée est la numéro 2.
	*
	* @return String	Retourne la chaine "La stratégie de type 2".
	*/
	public String affiche()
	{
		return super.affiche() + "2";
	}
}


/**
* <h1>Class Stratégie 3</h1>
*
* <p>
* Cette classe permet au joueur de se déplacer à l'aide du calcul suivant :</br>
* <ul>
*		<li>Valeur du dé + (position du joueur - position du dernier) / 2</li>
*		<li>Si le dé a pour valeur 1 ou 2, le déplacement est positif, sinon il est négatif.</li>
* </ul>
* </p>
*
* @see Strategie
* @see Jeux#affecteUneStrategieAleatoire
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Strategie3 extends Strategie
{
	/**
	* Constructeur de la Stratégie 3 identique à celui de la classe mère.
	*
	* @param j	Tableau de joueur sur lequel effectuer les actions.
	* @param nbJoueurs	Nombre de joueurs à prendre en compte dans le tableau de joueurs.
	* @param numJoueur	Numéro du joueur auquel il faudra affecter une stratégie.
	*/
	public Strategie3(Joueur[] j, int nb, int num)
	{
		super(j, nb, num);
	}
	
	/**
	* Permet au joueur de se déplacer d'une distance égale à la valeur du dé + (position du joueur - position du dernier) / 2.</br>
	* De plus, si le dé a pour valeur 1 ou 2, le déplacement est positif, sinon il est négatif.
	*                                            
	* @param d	Distance à prendre en compte dans les calculs de déplacement.
	*/
	public int changePosition(int d)
	{
		/** Contient la position du joueur en dernière position.*/
		int lowest = joueur[numeroDeJoueur].position();
		
		// Obtention de la position du joueur en dernière position
		for(int i = 2 ; i < nombreDeJoueur ; i++)
		{
			if(joueur[i].position() < lowest)
				lowest = joueur[i].position();
		}
		
		/** Contient le résultat du calcul donnant la distance absolue que le joueur va parcourir.*/
		int change = d + (joueur[numeroDeJoueur].position() - lowest) / 2;
		
		return(d == 1 || d == 2) ? change : -change;
	}
	
	/**
	* Annonce que la stratégie adoptée est la numéro 3.
	*
	* @return String	Retourne la chaine "La stratégie de type 3".
	*/
	public String affiche()
	{
		return super.affiche() + "3";
	}
}


/**
* <h1>Class Jeux</h1>
*
* <p>
* Cette classe permet de créer un jeu et tout ce qui l'entoure, puis de lancer le mécanisme de jeu.
* </p>
*
* @see Joueur
* @see Strategie
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
class Jeux
{
	/**
	* Tableau de joueur.
	*
	* @see Joueur
	*/
	private Joueur[] tabJoueurs;
	
	/** Création d'un nombre aléatoire qui servira pour la durée de la stratégie.*/
	private java.util.Random rnd = new java.util.Random();
	
	/** Nombre de joueur en lice.*/
	private int nombreDeJoueurs;
	
	/** Indenteur de boucle.*/
	private int i;
	
	/**
	* Créateur de jeu initialisant le générateur de nombres aléatoires, créant les joueurs et leur attribuant à chacun une stratégie aléatoire.
	*
	* @param nombreJoueurs	Nombre de joueurs à créer dans la partie.
	*
	* @see Joueur#Joueur
	* @see Strategie
	* @see Joueur#affecteStrategie
	* @see Jeux#affecteUneStrategieAleatoire
	*/
	public Jeux(int nombreJoueurs)
	{
		/** Nombre de joueurs à créer.*/
		nombreDeJoueurs = nombreJoueurs;
		
		/** Tableau contenant le nombre de joueurs demandé en paramètre.*/
		tabJoueurs = new Joueur[nombreDeJoueurs + 1];
		
		// Initialisation du Générateur de nombre Aléatoire
		for(i = 0 ; i < 5000 ; i++)
			rnd.nextDouble();
		
		// Création dynamique des objets Joueurs
		for(i = 1 ; i <= nombreDeJoueurs ; i++)
			tabJoueurs[i] = new Joueur(i, rnd);
		
		// On attribue une Strategie aléatoire à chaque joueur
		for(int joueurNumero = 1 ; joueurNumero <= nombreDeJoueurs ; joueurNumero++)
			affecteUneStrategieAleatoire(tabJoueurs[joueurNumero]);
	}
	
	/**
	* Permet de décerner une stratégie de manière aléatoire au joueur passé en paramètre.
	*
	* @param joueur	Joueur auquel va décerner une nouvelle stratégie.
	*
	* @see Joueur#affecteStrategie
	* @see Strategie
	*/
	public void affecteUneStrategieAleatoire(Joueur joueur)
	{
		// Affecte une stratégie Aléatoire au joueur
		switch(1 + rnd.nextInt(3))
		{
			case 1:
				joueur.affecteStrategie(new Strategie1(tabJoueurs, nombreDeJoueurs, joueur.numero() ));
				break;                                                               
			case 2:                                                                  
				joueur.affecteStrategie(new Strategie2(tabJoueurs, nombreDeJoueurs, joueur.numero() ));
				break;                                                               
			case 3:                                                                  
				joueur.affecteStrategie(new Strategie3(tabJoueurs, nombreDeJoueurs, joueur.numero() ));
		}
	}
	
	/**
	* Permet de lancer la partie et faire jouer les joueurs tour à tour, tant qu'il n'y aura pas de gagnant.
	*
	* @see Joueur
	* @see Strategie
	*/
	public void joue()
	{
		/** Initilisation de l'ordre de jeu.*/
		int joueurNumero = 0;
		
		// On boucle tant qu'il n'y a pas de gagnant
		do
		{
			// On passe au joueur suivant
			joueurNumero++;
			
			// Si on a fait le tour des joueurs, on revient au premier
			if(joueurNumero > nombreDeJoueurs)
				joueurNumero = 1;
			
			// Si la durée de stratégie est écoulée, on affecte une nouvelle stratégie aléatoire au joueur
			if(tabJoueurs[joueurNumero].dureeStrategie() == 0)
				affecteUneStrategieAleatoire(tabJoueurs[joueurNumero]);
			
			// Déplacement du joueur
			tabJoueurs[joueurNumero].deplace(1 + rnd.nextInt(6));
			
			// Affichage de la position du joueur
			System.out.println("Joueur " + joueurNumero + " positition: " + tabJoueurs[joueurNumero].position());
		}while(!tabJoueurs[joueurNumero].gagnant());
		
		// Affichage du gagnant
		System.out.println("\n\n<=========================> Joueur " + joueurNumero + " gagne le jeu. <=========================>");
	}
}


/**
* <h1>Class ExoQuatre</h1>
*
* <p>
* Cette classe principale crée, puis lance une partie.
* </p>
*
* @see Joueur
* @see Strategie
* @see Jeux
*
* @author Anice Khomany
* @version 0.1 : Date : Tue Feb 4 2014
*/
public class ExoQuatre
{
	/**
	* Méthode principale créant et lançant la partie.
	*
	* @see Joueur
	* @see Strategie
	* @see Jeux
	*/
	public static void main(String[] args)
	{
		System.out.println("\n\n<=================================== ExoQuatre ===================================>\n");
		
		/** Initialisation du jeu avec 10 joueurs.*/
		Jeux jeu = new Jeux(10);
		
		/** Lancement du jeu.*/
		jeu.joue();
		
		System.out.println("\n<================================================================================>\n");
	}
}











