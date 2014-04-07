/*
 * Question 1 :
 * 0
 * 0
 * 1
 * 1
 *
 *_______________
 * Question 2 :
 * Il y a deux classes publiques dans le même fichier.
 * Il faudrait enlever le public devant C.
 *
 * Question 3 :*/
public void inc(){
    int k = 0;
    k ++;
}

C : c = 0 - 0 - S = null
d = 3,14

/* 
 *Question 4 : */
C c new D() --> c() --> i = 1
D.f() --> c.f() --> i =1
c.f() --> D.f() --> C.f() --> i =1  -j =1

i = 1 - j = 0
i = 1 - j = 1




/*
 *Exercice 2

 Oui
 capture d'une exception NotANumberException



 Exercice 3
 */

public class Point {
    private double x, y;

    public int equals (Object o){

        Point p = o;

        if (this.x == p.x && this.y == p.y){

            return 1;
        }
        else return 0;
    }

    public double getX(){ return x;}
    public double getY(){return y;}
}

public class Droite {

    private double a, b;

    public Droite(Double a, Double b){

        this.a = a;
        this.b = b;
    }

    public Droite(Point x, Point y){

        try {
            if x.equals(y) {
                throw new PointsConfondusException(x, y);
            }
            else {
                this.a = ((x.y - y.y)/(x.x - y.x));
                this.b = x.y - a * x.x;
            }
        }
        catch(PointsConfondusException e){ System.out.println(e);}
    }
}



/*
 * Exercice 4 
 * Question 1
 */

public Point3D {

    private double x, y, z;

    public Point3D (double x, double y, double z){

        this.x = x;
        this.y = y;
        this.z = z;
    }

    public String toString(){

        return "[Point3D x : " + x +" , y : " + y + ", z : " + z + "]";
    }
}

public abstract Forme {

    private Point3D gravité;
    private double densité;

    protected static Arraylist listeformes;
   
}

public class Brique extends Forme {

    private double largeur;
    private double longueur;
    private double hauteur;

    public Brique (Point3D g, double d, double la, double lo, double h){

        this.gravité = g;
        this.densité = d;
        this.largeur = la;
        this.longueur = lo;
        this.hauteur = h;
    }

    public double calculerSurface() {

        return (2 * (largeur * longueur + largeur * hauteur + longueur * hauteur));
    }

    public double calculerVolume(){

        return calculerSurface() * hauteur;
    }
