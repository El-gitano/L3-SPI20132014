import java.util.LinkedList;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		Simulateur sim = new Simulateur();
		sim.simuler();

		System.out.println("Test des bases de données\n");
		
		LinkedList<BaseDeDonnees<String>> lstBdd = new LinkedList<BaseDeDonnees<String>>();
		
		lstBdd.add(new BaseDeDonnees<String>(new TriJava()));
		lstBdd.add(new BaseDeDonnees<String>(new TriBulle()));
		lstBdd.add(new BaseDeDonnees<String>(new TriInsertion()));
		
		for(BaseDeDonnees<String> bdd : lstBdd){
			
			bdd.ajouter("Hello");
			bdd.ajouter("World");
			bdd.ajouter("Test");
			bdd.ajouter("De ouf");
			bdd.ajouter("Colvert");
			bdd.ajouter("Mandarin");
			bdd.ajouter("minuscule");
			bdd.ajouter(";expresiion bizarre");
			bdd.ajouter("FiN");
		}
		
		lstBdd.get(0).afficheDonneesnonTriees();
		System.out.println("\n");
		
		for(BaseDeDonnees<String> bdd : lstBdd){
			
			bdd.afficheDonneesTriees();
			System.out.println("\n");
		}
	}

}
