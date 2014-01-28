/**
* Cette classe représente un Triangle composé de trois Points dans un espace 2 dimensions.
* @see Point
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Jan 28 09:39:42 CET 2014
*
*/
public class Triangle {

	private Point a;
	private Point b;
	private Point c;

/**
 * 	Crée une instance de la classe à partir de trois points passés en paramètre
 * 	@param p Points utilisés pour la création du triangle
 * 		@see Points
 */
	public Triangle(Point p1, Point p2, Point p3){

		this.a = p1;
		this.b = p2;
		this.c = p3;
	}

/**
 * 	Crée une instance de la classe à partir de trois droites passées en paramètre
 * 	@param d1, d2, d3
 * 		Droites utiliséss pour la création du triangle
 * 		@see Droites
 */
	public Triangle(Droite d1, Droite d2, Droite d3){

		this.a = d1.intersection(d2);
		this.b = d2.intersection(d3);
		this.c = d3.intersection(d1);
	}

/**
 * 	Retourne la périmètre d'une instance de la classe Triangle
 * 	@return perimètre du triangle
 */
	public double perimetre(){

		return a.distance(b) + a.distance(c) + b.distance(c);
	}

/**
 * 	Retourne la surface d'une instance de la classe Triangle
 * 	@return surface du triangle
*/
	public double surface(){

		double perim = perimetre();

		//On a A = rac( (p * (p-a) * (p-b) * (p-c)) /16) avec p le périmètre du triangle, a, b et c la longueur des cotés
		return Math.sqrt( (perim * (perim - a.distance(b)) * (perim - a.distance(c)) * (perim - b.distance(c))) / (double)16);
	}

/**
 * 	Retourne une chaine de caractère présentant les points composant le triangle
 * 	@return String
 */
	public String donnerPoints(){

		return new String(a.toString() + ":" + b.toString() + ":" + c.toString());
	}
}