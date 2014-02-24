//TD sur les véhicules, intitulé TD VROUM

public class Vehicule {
    protected int nbRoues;

    public void demarrer(){};
    public void rouler(){};
    public void arreter(){};

    public String categorie(){

        return "je suis un vehicule";
    }

    public void description(){

        System.out.println(categorie() + " a " + nbRoues + " roues");
    }
}

//Question 1 ecrire les classes Voiture, Bus et Fiat.

public class Voiture extends Vehicule {

    public Voiture(){

        nbRoues = 4;
    }

    public categorie (){
        return "je suis une voiture!";
    }
}

public class Bus extends Vehicule {

    public Bus (){

        nbRoues = 6;
    }

    public categorie() {
        
        return "je suis un Bus!";
    }
}

public class Fiat extends Voiture {

    public Fiat() {
        super();
    }

    public categorie() {

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
