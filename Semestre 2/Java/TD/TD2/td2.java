
//td du 04/02/2014 --> Suite du TD1
//Les fonctions produits, difference et quotient  ont déjà été déclarés
//
import java.util

//Q6
public static Rationnel [] trinome(Rationnel [] coeffs, Rationnel precession) {
    
    Rationnel res [];
    Rationnel delta = (coeffs[1].produit(coeffs[1])).difference(coeffs[0].produit(coeffs[2]).produit(new Rationnel(4, 1)));
    
    switch(delta.CompareTo(new Rationnel(0, 1))){
            
            case 0 : {
                         res = new Rationnel[1];
                         res[0] = (coeffs[1].produit(new Rationnel(-1, 1))).quotient(coeffs[0].produit(new Rationnel(2, 1)));
                         break;
            }
            case 1: {
                        res = new Rationnel[2];
                        res[0] = (Rationnel.sqrt(delta, precision).difference(coeffs[1])).quotient(coeffs[0].produit(new Rationnel(2, 1)));
                        res[1] = (Rationnel.sqrt(delta, precision).produit(new Rationnel(-1, 1)).difference(coeffs[1].produit(new Rationnel(-1, 1)))).quotient(coeffs[0].produit(new Rationnel(2, 1)));
                        break;
            }
            case -1: {
                         res = new Rationnel[0];
                         break;
            }
    }
}


/*
 * TD2 : Exercice 1
 * Soit B une sous classe de A
 * A a1 = new A();
 * A a2 = new A();
 * B b1 = new B();
 * a1 = a2;
 * b1 = a2;
 * a2 = b1;
 * La première instruction est correcte.
 * La seconde est fausse a2 instanceOf B -> false
 * La troisième est fausse
 *
 * Exercice 2 :
 * m1 et m2 sont des instances declasse mères, d1 et d2 sont des instances de classes filles
 * m1.methode(m2) -> appelle à la méthode de la classe mère et réussit
 * m1.methode(d1) -> appelle à la méthode de la classe mère, et comme d1 instanceOf Mother -> true, la méthode réussit
 * d1.methode(m1) -> appelle à la méthode de la classe mère via la classe fille, méthode réussit
 * d1.methode(d2) -> appelle à la méthode de la classe fille, réussie.
 *
 * Exercice 3:
 * 
 */

