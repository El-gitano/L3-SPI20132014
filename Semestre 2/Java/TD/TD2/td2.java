
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
 * Question 1
 * cas n°1 -> Il fonctionne, affiche "La cigarette...", et vieillit.
 *
 * Cas n°2 -> Ne fonctionne pas, EtreHumain est une classe mère, elle ne peut pas être attribué à une objet de classe Shakira.
 *
 * Cas n°3 -> Ne fonctionne pas, Sarkozy étant un HommePolitique, il ne chante pas (il n'a pas la méthode)
 *
 * Cas N°4 -> Ne fonctionne pas, car les EtreHumain n'ont pas de méthode chanter, ce qui provoque une erreur à la compilation
 *
 * cas n°5 -> Fonctionne, car on a casté la méthode via la classe Chanteur, et affiche "La cigarette..."
 *
 * cas n°6 -> Fonctionne jusqu'à la dernière ligne, qui provoque une erreur de compilation
 *
 * Question 2 : 
 */
class EtreHumain {
    public String toString() {
        return "Je suis un être humain agé de " + age + "années";
    }
}
/*
 *
 * Question 3 :
 */
abstract class HommePolitique extends EtreHumain {
    public String toString() {
        return super.toString() + "et je peux débattre" + debattre();
    }
}
abstract class Chanteur extends EtreHumain {
    public String toString() {
        return super.toString() + " et je peux chanter " + chanter();
    }
}

/* Exercice 4
 *
 * 
 * Les classes à définir :
 * -Joueur(attributs : score, numéro de joueur, Stratégie, durée de stratégie, random rnd; méthodes : Joueur(int, random), boolean gagnant(), void deplace(int), void affectStratégie, int dureeStratégie(), int position())
 * -Jeu (attributs : tableau de joueur, dernier joueur, premier joueur, nbre de joueur; méthode : affecte une stratégie aléatoire, Jeux(), joue()
 * Stratégie (Joueur [] joueur, int nbreDetour, int numeroDeJoueur; méthode int changePosition()) -> Trois classes filles, stratégie1, stratégie2, stratégie3, dans lesquelles on redéfinit int ChangePosition()
 *
 */

class Jeux {
    
    private Joueur [] joueurs = new Joueur[5];
    private java.util.Random rnd = new java.util.Random();
    private int nbreDeJoueurs;

    //Constructeur
    public Jeux(int nbreJoueurs){
        
        this.nbreDeJoueurs = nombreJoueurs;
        //Initialisation du Générateur de nbre aléatoires
        for (int i = 0; i < 50000; i ++)
            rnd.nextDouble();
        //Création des Joueurs
        joueurs[1] = new Joueur(1, rnd);
        joueurs[2] = new Joueur(2, rnd);
        joueurs[3] = new Joueur(3, rnd);
        joueurs[4] = new Joueur(3, rnd);

        //on attribue une stratégie aléatoire à chaque joueur
        for(int joueurNumero = 1; joueurNumero <= nbreJoueurs; joueurNumero ++)
            affecteUneStrategieAleatoire(joueurs[joueurNumero]);
    }
    public void affecteUneStrategieAleatoire (Joueur joueur) {
    }

    public void joue() {
        
        int joueurNumero = 0;
        
        do {
            
            joueurNumero ++;
            
            if (joueurNumero > nbreDeJoueurs)
                
                joueurNumero = 1;

            if(joueurs[joueurNumero].dureeStrategie() == 0)

                affecteUneStrategieAleatoire(joueurs[joueurNumero]);
            joueurs[joueurNumero].deplace(1 + rnd.nextInt(6));

            System.out.println ("Joueur " + joueurNumero + "position : " + joueurs[joueurNumero].position());

        }while(!joueurs[joueurNumero].gagnant());

        System.out.println("\n\tJoueur " + joueurNumero + "gagne le jeu.");

    }
}


public class Joueur {
    
    private int position;
    private int numeroDeJoueur;
    private Strategie str;
    private int dureeStrategie;
    private Random rnd;

    public Joueur(int numeroJoueur,Java.util.Random rand) {

        this.position = 0;
        this.numeroDeJoueur = numeroJoueur;
        this.rnd = rand;
    }

    public int dureeStrategie() {
        return dureeStrategie;
    }

    public int position(){
        return position;
    }

    public boolean gagnant() {

        return (position >= 500);
    }

    public affectStrategie(Strategie s){

        str = s;
        dureeStrategie = rnd.nextInt(4) + 2;
        System.out.println("J'affecte au Joueur " + numeroDeJoueur + "la stratégie " str + ", pour une durée de " + dureeStrategie);
    }

    public void deplace(int valeur){

        dureeStrategie --;
        position = str.changePosition(valeur);
        System.out.println("Joueur "+ numeroDeJoueur + " position " + position);
    }
    
}

public abstract class Strategie {

    Joueur[] joueurs;
    int nombreDeJoueur;
    int numeroDeJoueur;

    public Strategie(Joueur[] j, int N, int numero) {
        this.joueur = j;
        this.numeroDeJoueur = numero;
        this.nombreDeJoueur = N;
    }

    public abstract changePosition(int d);
}

public class Strategie1 extends Strategie {

    public Strategie(Joueur[] j, int n, int m) {
        
        super(j, n, m);
    }

    public int changePosition(int d) {
        
        int highest = joueur[1].position();
        for(int i = 2; i < nombreDeJoueur, i ++)
            if(joueur[i].position() > highest)
                highest = joueur[i].position();

        int change = d + (highest - joueur[numeroDeJoueur].position())/2;
        return (d / 2) ? change : -change;
    }
}
