/**
* Cette classe représente une droite à partir de son équation
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Jan 28 09:56:16 CET 2014
*
*/
public class Droite {

/**	Coefficient directeur de la droite*/
	double a;
/**  Ordonnée à l'origine de la droite*/
	double b;

/** 	Accesseur du coefficient directeur
	@return double coefficient directeur
*/
	public double getA(){

		return this.a;
	}

/** 	Accesseur de l'ordonnée à l'origine
	@return double Ordonnée à l'origine
*/
	public double getB(){

		return this.b;
	}

/**	Cette méthode crée une droite à partir de deux paramètres
 * 	@param a
 * 		Le coefficient directeur
 * 	@param
 * 		L'ordonnée à l'origine
 */
	public Droite(double a, double b){

		this.a = a;
		this.b = b;
	}

/**	Cette méthode crée une droite à partir de deux Points
 * 	@param p1, p2
 * 		Points appartenants à la droite
 */
	public Droite(Point p1, Point p2){

		if(p1.getX() != p2.getX()){
			
			//Coeff. directeur = (yB - yA) / (xB - xA)
			this.a = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());

			//On calcule b = yA - (coeff.directeur * xA)
			this.b = p1.getY() - this.a * p1.getX();
		}
		//Droite verticale (cas particulier)
		else{

			this.a = Double.POSITIVE_INFINITY;
			this.b = Double.NaN;
		}
	}

/**	Cette méthode retourne vrai si la droite est parallèle à celle passée en paramètre
 * 	@param d
 * 		Droite à comparer à celle de l'instance
 * 		
 * 	@return Bolléen testant la condition
 */
	public boolean estParallele(Droite d){

		return this.a == d.getA();
	}

/**	Cette méthode retourne un Point, fruit de l'intersection de deux droites
 * 	@see Points
 * 	@param d
 * 		Droite servant à l'intersection avec celle de l'instance 
 * 	@return Point d'intesection
 */
	public Point intersection(Droite d){

		double xInt = (d.getB() - b) / (a - d.getA());
		double yInt = (xInt * a) + b;

		return new Point(xInt, yInt);
	}
}