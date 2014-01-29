/**
 * Classe chargée de tester les classes Point, Triangle et Droite
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Jan 28 10:28:22 CET 2014
*
* @see Point
* @see Triangle
* @see Droite
*/
public class Test {

	public static void main(String args[]){

		Point p1 = new Point(1, 2);
		Point p2 = new Point(4, 7);
		Point p3 = new Point(3, 9);
		Point p4 = new Point(1, 2);

		Droite d1 = new Droite(p1, p2);
		Droite d2 = new Droite(p2, p3);
		Droite d3 = new Droite(p3, p1);
		
		Triangle t1 = new Triangle(p1, p2, p3);
		Triangle t2 = new Triangle(d1, d2, d3);
		
		System.out.println("Distance p1 - p2 : " + p1.distance(p2));
		System.out.println("Distance p2 - p1 : " + p2.distance(p1));
		System.out.println("Distance p1 - p3 : " + p1.distance(p3));
		
		System.out.println("Test égalité p1 - p2 " + p1.equals(p2));
		System.out.println("Test égalité p2 - p1 " + p2.equals(p1));
		System.out.println("Test égalité p1 - p1 " + p1.equals(p1));
		System.out.println("Test égalité p1 - p4 " + p1.equals(p4));
		
		System.out.println("Coordonnées d1 : (" + d1.getA() + " : " + d1.getB() + ")");
		System.out.println("Coordonnées d2 : (" + d2.getA() + " : " + d2.getB() + ")");

		System.out.println("Point du triangle t1 : (" + t1.donnerPoints() + ")");
		System.out.println("Périmètre du triangle t1 : (" + t1.perimetre() + ")");
		System.out.println("Surface du triangle t1 : (" + t1.surface() + ")");
		
		System.out.println("Point du triangle t2 : (" + t2.donnerPoints() + ")");
		System.out.println("Périmètre du triangle t2 : (" + t2.perimetre() + ")");
		System.out.println("Surface du triangle t2 : (" + t2.surface() + ")");

		System.out.println("p1 appartient à d1 : " + p1.estSurDroite(d1));
		System.out.println("p1 appartient à d2 : " + p1.estSurDroite(d2));
	}
}