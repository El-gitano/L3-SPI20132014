//TD sur les véhicules, intitulé TD VROUM

abstract public class Vehicule implements Avertir{
    protected int nbRoues;

    public void demarrer(){};
    public void rouler(){};
    public void arreter(){};

    public String categorie(){

        return "je suis un vehicule";
    }

    abstract public void klaxonner

    public void description(){

        System.out.println(categorie() + " a " + nbRoues + " roues");
    }
}

//Question 1 ecrire les classes Voiture, Bus et Fiat.

public class Voiture extends Vehicule {

    public Voiture(){

        nbRoues = 4;
    }

    public String categorie (){
        return "je suis une voiture!";
    }

    public void klaxoner(){

        System.out.println("Pouet Pouet");
    }
}

public class Bus extends Vehicule {

    public Bus (){

        nbRoues = 6;
    }

    public String categorie() {
        
        return "je suis un Bus!";
    }

    public void klaxonner(){

        System.out.println("Tut Tuut");
    }
}

public class Fiat extends Voiture {

    public Fiat() {
        super();
    }

    public String categorie() {

        return "je suis une Fiat";
    }
}

public class Client {

    public static void main(String args[]) {

        Vehicule v;
        v = new Vehicule();
        v.description();
        v = new Voiture();
        v.description();
        v = new Bus();
        v.description();
        v = new Fiat();
        v.description();
    }
}

//Question 2 : passr la méthode categorie() en private fait que ce n'est plus une rédéfinition de méthode dans les sous classe, ce qui implique que l'héritage et le polymorphisme ne se mettent pas en place.


//Question 3
interface Avertir {

    public klaxoner(){};
}
