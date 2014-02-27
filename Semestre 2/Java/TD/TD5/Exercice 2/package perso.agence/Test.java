import java.util.Iterator;

public class Test{

	public static void main(String [] args){
	
		//Création de l'agence, des voitures et des critères
		Agence a = new Agence();
		
		Voiture v1 = new Voiture("citroën", "c1", 1990, 90);
		Voiture v2 = new Voiture("citroën", "c2", 2007, 150);
		Voiture v3 = new Voiture("citroën", "c3", 2000, 120);
		
		Voiture v4 = new Voiture("opel", "o1", 1993, 90);
		Voiture v5 = new Voiture("opel", "o2", 2004, 170);
		Voiture v6 = new Voiture("opel", "o3", 1980, 20);
		
		Voiture v7 = new Voiture("renault", "r1", 1991, 950);
		Voiture v8 = new Voiture("renault", "r2", 2009, 140);
		Voiture v9 = new Voiture("renault", "r3", 1984, 60);
		
		CriterePrix c1 = new CriterePrix(100);
		CritereMarque c2 = new CritereMarque("opel");
		
		InterCritere c3 = new InterCritere();
		c3.add(c1);
		c3.add(c2);
		
		//A l'arrache mais ça fonctionne
		a.add(v1);
		a.add(v2);
		a.add(v3);
		a.add(v4);
		a.add(v5);
		a.add(v6);
		a.add(v7);
		a.add(v8);
		a.add(v9);
		
		//Critère de prix
		Iterator i = a.selectionne(c1).iterator();
		
		while(i.hasNext()){
		
			System.out.println(i.next());
		}
		
		System.out.print("\n");
		
		//Intercritère
		i = a.selectionne(c3).iterator();
		
		while(i.hasNext()){
		
			System.out.println(i.next());
		}
	}
}
