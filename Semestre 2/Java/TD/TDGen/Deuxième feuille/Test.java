import java.util.Date;
import java.util.List;

public class Test{

	public static void main(String[] args){
	
		ArbreBinaireRecherche<Integer> ab = new ArbreBinaireRecherche<Integer>(5);
		ArbreBinaireRecherche<String> ab2 = new ArbreBinaireRecherche<String>("Test");

		try{
		
			ab.inserer(2);
			//ab.inserer(2); //Test doublon
			ab.inserer(4);
			ab.inserer(7);
			ab.inserer(23);
			ab.inserer(1);
			ab.inserer(67);
			ab.inserer(21);
			ab.inserer(99);
			ab.inserer(200);
			
			//ab.afficherPostfixe();
			//ab.afficherPrefixe();
			//ab.afficherInfixe();
			//ab.afficherDepuisListe();
			
			ab2.inserer("Antoine");
			ab2.inserer("Anice");
			ab2.inserer("Rémi");
			ab2.inserer("Colas");
			ab2.inserer("Lucas");
			ab2.inserer("Ewen");
			ab2.inserer("Erwan");
			ab2.inserer("Julien");
			ab2.inserer("Elyan");
			/*
			ab2.afficherPostfixe();
			ab2.afficherPrefixe();
			ab2.afficherInfixe();
			*/
			Enseignant jacoboni = new Enseignant("Jacoboni", "Pierre", new Date(), EnumStatut.ARPETE);
			Enseignant despres = new Enseignant("Despres", "Christophe", new Date(), EnumStatut.ARPETE);
			
			Etudiant anice = new Etudiant("Khomany", "Anice", new Date(), EnumNiveau.EXCELLENT);
			Etudiant colas = new Etudiant("Picard", "Colas", new Date(), EnumNiveau.EXCELLENT);
			Etudiant remi = new Etudiant("Tremblain", "Rémi", new Date(), EnumNiveau.EXCELLENT);
			
			Personne p1 = new Personne("UnNom", "UnPrenom", new Date());
			Personne p2 = new Personne("UnNom2", "UnPrenom2", new Date());
			Personne p3 = new Personne("UnNom3", "UnPrenom3", new Date());
			
			ArbreBinaireRecherche<Personne> ab3 = new ArbreBinaireRecherche<Personne>(jacoboni);
			
			ab3.inserer(despres);
			ab3.inserer(anice);
			ab3.inserer(colas);
			ab3.inserer(remi);
			ab3.inserer(p1);
			ab3.inserer(p2);
			ab3.inserer(p3);
			
			//ab3.afficherInfixe();
			
			System.out.println("Affichage par ordre naturel");
			ab3.afficherDepuisListe();
			
			System.out.println("Affichage par age");
			ab3.afficherDepuisListe(new ComparateurPersonneAge());
			
			System.out.println("Affichage par nom");
			ab3.afficherDepuisListe(new ComparateurPersonnePrenom());
			
		}
		catch (DoublonException e){
		
			System.out.println("Erreur lors de l'ajout des Integers dans l'arbre : " + e.getMessage());
		}
	
	}
}
