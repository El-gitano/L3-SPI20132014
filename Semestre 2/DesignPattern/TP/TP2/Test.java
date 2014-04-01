/**
 * Classe de test des différents execices du TP
 * @author Antoine Foucault
 *
 */
public class Test {

	public static void main(String[] args) {
		
		Fichiers a = new Fichier("a", 12, "Le contenu de A");
		Fichiers b = new Fichier("b", 54, "Le contenu de B");
		Fichiers c = new Fichier("c", 32, "Le contenu de C");
		Fichiers d = new Fichier("d", 62, "Le contenu de D");
		Fichiers e = new Fichier("e", 82, "Le contenu de E");
		Fichiers f = new Fichier("f", 102, "Le contenu de F");
		
		Fichiers[] tabFich = new Fichiers[4];
		tabFich[0] = a;
		tabFich[1] = b;
		tabFich[2] = c;
		tabFich[3] = d;
		
		VisiteurConcretA v1 = new VisiteurConcretA();
		VisiteurConcretB v2 = new VisiteurConcretB();
		
		//Constitution de la hierarchie des dossiers de tests
		Dossier d3 = new Dossier("dossier3");
		Dossier d4 = new Dossier("dossier4");
		d4.add(b, e, f);
		
		Dossier d1 = new Dossier("dossier1");
		Dossier d2 = new Dossier("dossier2");
		d2.add(a, (Fichiers)d3, c);
		d1.add((Fichiers)d2, d, (Fichiers)d4);

		
		//Test système de fichiers
		System.out.println("\n===== Test du système de fichiers =====\n");
		
		SystemeFichier sFichier = new SystemeFichier(tabFich);

		int tailleMax = 0;
		
		for(Fichiers fTemp : sFichier){
			
			System.out.println("Parcours du fichier/dossier : " + fTemp);
			
			if(fTemp.getTaille() > tailleMax){
				
				tailleMax = fTemp.getTaille();
			}
		}
		
		System.out.println("TailleMax = " + tailleMax);
		
		//Test du parcours d'un dossier avec itérateur + composite
		System.out.println("\n===== Test du parcours d'un dossier =====\n");
		
		for(Fichiers fTemp : d1){
			
			System.out.println("On passe sur le fichier : " + fTemp);
		}
		
		System.out.println("\n===== Test du visiteur 1 =====\n");
		
		for(Fichiers fTemp : d1){
			
			fTemp.accepte(v1);
		}
		
		System.out.println("\n===== Test du visiteur 2 =====\n");
		
		for(Fichiers fTemp : d1){
			
			fTemp.accepte(v2);
		}
		
		System.out.println("Le fichier le plus vieux est : " + v2.getPlusVieux());
	}

}
