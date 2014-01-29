/**
* Cette classe représente un point d'un espace deux dimensions
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Jan 28 09:06:40 CET 2014
*
*/
public class Point {

/**	Représente la coordonnée x du point*/
	private double x;
	
/**	Représente la coordonnée y du point*/
	private double y;

/**	Crée une instance de la classe Point à l'aide de deux coordonnées passés en paramètre
 * 	@param x 
 * 		La coordonnée x du point
 * 	@param y 
 * 		La coordonnée y du point
 */
	public Point(double x, double y){

		this.x = x;
		this.y = y;
	}

/**
 * Accesseur de la coordonnée x du point
 */
	public double getX(){

		return this.x;
	}

/**
 * Accesseur de la coordonnée x du point
 */
	public double getY(){

		return this.y;
	}
	
	public boolean equals(Object obj){

		//On effectue une "vérification générique"
		if(this == obj){

			return true;
		}
		else if(obj == null){

			return false;
		}
		else if(getClass() != obj.getClass()){

			return false;
		}

		//On sait que les objets sont de la meme classe, on peut donc comparer leurs champs
		Point autre = (Point) obj;

		if( (this.x == autre.x) && (this.y == autre.y) ){

			return true;
		}
		else{

			return false;
		}
	}

	//En rédéfinissant equals() on doit redéfinir hashCode()
	public int hashCode(){

		return (int)this.x + (int)this.y;
	}

	public double distance(Point p){

		double disX = p.getX() - this.x;
		double disY = p.getY() - this.y;

		return Math.hypot(disX, disY);
	}

/**
 * Méthode chargée de vérifier si un point appartient à une droite
 * 
 * @param d
 * 	La droite sur laquelle on doit vérifier l'appartenance du point
 * 	
 * @return Un booléan caractérisant l'appartenance du point à la droite passée en paramètre
 * 
 * @see Droite
 */
	public boolean estSurDroite(Droite d){

		return this.y == (this.x * d.getA()) + d.getB();
	}

	public String toString(){

		return new String("(" + x + " : " + y + ")");
	}
}