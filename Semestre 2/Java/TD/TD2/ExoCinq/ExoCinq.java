/**
* <h1> Class Décaleur </h1>
*
* <p>
* Le décaleur permet de faire défiler des caractères sur une largeur prédéfinie.
* </p>
*
*
* @author Anice Khomany
* @version 0.1 : Date : Thu Feb 13 2014
*/
class Decaleur
{
	/** Correspond à l'écran d'affichage du décaleur. La taille de la chaîne sera le nombre de caractères affichable à l'écran.*/
	private char[] msg;
	
	/**
	* Créateur de décaleur auquel on fournit la taille du décaleur à créer.
	* On remplit alors d'espaces la chaine créée.
	*/
	public Decaleur(int decaleurSize)
	{
		// On réserve une taille donnée en paramètre
		msg = new char[decaleurSize];
		// On remplit d'espace le décaleur
		raz();
	}
	
	/**
	* Accesseur de la largeur du décaleur pour les autres classes.
	*
	* @return int Largeut du décaleur
	*/
	public int getLargeur()
	{
		return msg.length;
	}
	
	/** Remplissage du décaleur par des espaces. */
	public void raz()
	{
		for(int i = 0 ; i < msg.length ; i++)
			msg[i] = ' ';
	}
	
	/**
	* Ajoute un caractère au décaleur et décale donc tous ceux présents jusqu'au premier qui est renvoyé par la méthode.
	*
	* @param c	Caractère à insérer dans le décaleur.
	*
	* @return char	Caractère placé en première position qui est "éjecté" avec le décalage.
	*/
	public char decale(char c)
	{
		/** Contient le caractère en première position à renvoyer.*/
		char tmp = msg[0];
		
		// Chaque caractère prend la valeur de celui qui suit
		for(int i = 0 ; i < msg.length - 1 ; i++)
			msg[i] = msg[i+1];
		
		// Le dernier vaut le caractère en paramètre
		msg[msg.length-1] = c;
		
		// On retourne l'ancien premier caractère
		return tmp;
	}
	
	/**
	* Affichage des caractères présents dans le décaleur.
	*
	* @return String	Chaine de caractères contenue dans le décaleur.
	*/
	public String toString()
	{
		return new String(msg);
	}
	
}


/**
* <h1> Class Afficheur </h1>
*
* <p>
* L'afficheur permet d'afficher un message sur le décaleur à l'aide d'une chaine de caractère passée en paramètre.
* </p>
*
* @see Decaleur
*
* @author Anice Khomany
* @version 0.1 : Date : Thu Feb 13 2014
*/
class Afficheur
{
	/** Décaleur à utiliser.*/
	private Decaleur d;
	/** Chaîne de caractères qui contiendra le message à afficher.*/
	protected char[] message;
	/** Indice permettant de connaître la position courante dans la chaîne de caractère.*/
	private int indCourant;
	
	/**
	* Crée un afficheur à l'aide d'une taille donnée en paramètre.
	*
	* @param afficheSize	Taille du décaleur et du message.
	*/
	public Afficheur(int afficheSize)
	{
		if(afficheSize > 0)
			d = new Decaleur(afficheSize);
		else
			System.out.println("Veuillez entrer un nombre entier positif pour la taille de l'afficheur.");
		
		// Le message à afficher est aussi long que le décaleur
		message = new char[afficheSize];
	}
	
	/**
	* Crée un afficheur à l'aide d'une taille et d'un message donnés en paramètre.
	*
	* @param afficheSize	Taille du décaleur et du message.
	* @param m	Message à afficher dans l'afficheur.
	*/
	public Afficheur(int afficheSize, char m[])
	{
		if(afficheSize > 0)
			d = new Decaleur(afficheSize);
		else
			System.out.println("Veuillez entrer un nombre entier positif pour la taille de l'afficheur.");
		
		setMessage(m);
	}
	
	/**
	* Mets en place le message à afficher dans l'afficheur à l'aide de la chaîne de caractère passée en paramètre.
	*
	* @param m	Message à afficher dans l'afficheur.
	*/
	public void setMessage(char[] m)
	{
		message = m;
		indCourant = 0;
	}
	
	/** Décale d'un cran l'affichage et donc l'indice dans la chaîne de caractères à afficher. */
	public void top()
	{
		// Décalage dans l'affichage
		d.decale(message[indCourant]);
		
		indCourant++;
		
		// Si on atteint la fin du message, on revient au début.
		if(indCourant >= message.length)
			indCourant = 0;
		
		// On peut aussi faire :
		// indCourant = (indCourant + 1) % (message.length);
	}
	
	/** Affichage du décaleur.*/
	public String toString()
	{
		return d.toString();
	}
}


/**
* <h1> Class Latence </h1>
*
* <p>
* La latence permet d'intercaler des espaces entre chaque affichage d'un mot.
* </p>
*
* @see Decaleur
* @ee Afficheur
*
* @author Anice Khomany
* @version 0.1 : Date : Thu Feb 13 2014
*/
class Latence extends Afficheur
{
	/** Nombre d'espaces à intercaler entre deux messages.*/
	int latence = 0;
	
	/**
	* Création d'un afficheur auquel on ajoute une latence.
	*
	* @param afficheurSize	Taille du décaleur et du message
	* @param lat	Nombre d'espaces à intercaler entre deux messages.
	*
	* @see Afficheur#Afficheur(int)
	*/
	public Latence(int afficheurSize, int lat)
	{
		super(afficheurSize);
		latence = lat;
	}
	
	/**
	* Mets en place le message à afficher dans l'afficheur à l'aide de la chaîne de caractère passée en paramètre.
	* On intercale à la fin du message le nombre d'espaces nécessaire à la latence.
	*
	* @param m	Message à afficher dans l'afficheur.
	*/
	public void setMessage(char[] m)
	{
		/** Nouvelle chaîne de caractères contenant le message suivi du nombre d'espaces demandé par la latence.*/
		char[] newMsg = new char[m.length + latence];
		
		// On remplit la nouvelle chaîne par l'ancien message
		for(int i = 0 ; i < m.length ; i++)
			newMsg[i] = m[i];
		
		// Puis on remplit la place restante d'espaces
		for(int i = m.length ; i < newMsg.length ; i++)
			newMsg[i] = ' ';
		
		message = newMsg;
		
		// On peut aussi faire sans le protected sur la variable message de la classe Afficheur avec :
		// super.setMessage(newMsg);
	}
}


/**
* <h1> Class Vitesse </h1>
*
* <p>
* La vitesse permet de prédéfinir le nombre de caractères à décaler à chaque décalage.
* </p>
*
* @see Decaleur
* @ee Afficheur
* @see Latence
*
* @author Anice Khomany
* @version 0.1 : Date : Thu Feb 13 2014
*/
class Vitesse extends Latence
{
	/** Nombre de caractères à décaler à chaque décalage.*/
	int speed = 0;
	
	/**
	* Créateur d'un afficheur qui a une latence et une vitesse.
	*
	* @param afficheurSize	Taille du décaleur et du message
	* @param lat	Nombre d'espaces à intercaler entre deux messages.
	* @param vitesse Nombre de caractères à décaler à chaque décalage.
	*/
	public Vitesse(int afficheurSize, int lat, int vitesse)
	{
		super(afficheurSize, lat);
		speed = vitesse;
	}
	
	/** Effectue un décalage prenant en compte la vitesse.*/
	public void top()
	{
		for(int i = 0 ; i < speed ; i++)
			super.top();
	}
}



/**
* <h1> Class ExoCinq </h1>
*
* <p>
* Classe permettant de tester le décaleur et toutes ses variantes en déscendant.
* </p>
*
* @see Decaleur
* @ee Afficheur
* @see Latence
* @see Vitesse
*
* @author Anice Khomany
* @version 0.1 : Date : Thu Feb 13 2014
*/
public class ExoCinq
{
	/** Méthode principale effectuant tous les tests.*/
	public static void main(String[] args)
	{
		System.out.println("\n\n<================== ExoCinq ==================>\n");
		
		// Déclaration des chaînes de caractères à utiliser
		char[] bonjour = {'b', 'o', 'n', 'j', 'o', 'u', 'r', ' ', 'l', 'o', 'l', ' '};
		char[] hello = {'h', 'e', 'l', 'l', 'o'};
		char[] salut = {'s', 'a', 'l', 'u', 't'};
		
		
		
		// Test de la classe Décaleur
		System.out.println("<==> Classe Décaleur <==>\n");
		Decaleur monDecaleur = new Decaleur(6);
		System.out.println("Taille du décaleur: " + monDecaleur.getLargeur());
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('c');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('o');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('u');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('c');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('o');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale('u');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale(' ');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale(' ');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.decale(' ');
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		monDecaleur.raz();
		System.out.println("<==> " + monDecaleur.toString() + " <==>");
		
		
		// Test de la classe Afficheur
		System.out.println("\n<==> Classe Décaleur <==>\n");
		Afficheur monAfficheur = new Afficheur(6);
		monAfficheur.setMessage(bonjour);
		
		for(int i = 0 ; i < 20 ; i++)
		{
			monAfficheur.top();
			System.out.println("<==> " + monAfficheur.toString() + " <==>");
		}
		
		
		
		// Test de la classe Latence
		System.out.println("\n<==> Classe Latence <==>\n");
		Latence maLatence = new Latence(6, 3);
		maLatence.setMessage(hello);
		
		for(int i = 0 ; i < 20 ; i++)
		{
			maLatence.top();
			System.out.println("<==> " + maLatence.toString() + " <==>");
		}
		
		
		// Test de la classe Vitesse
		System.out.println("\n<==> Classe Vitesse <==>\n");
		Vitesse maVitesse = new Vitesse(6, 3, 2);
		maVitesse.setMessage(salut);
		
		for(int i = 0 ; i < 20 ; i++)
		{
			maVitesse.top();
			System.out.println("<==> " + maVitesse.toString() + " <==>");
		}
		
		System.out.println("\n<==============================================>\n");
	}
}