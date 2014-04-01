/**
 * Ce visiteur affiche le nom des fichiers situés au premier niveau des dossiers ou le contenu des fichiers qu'il parcours
 * @author Antoine Foucault
 *
 */
public class VisiteurConcretA implements Visiteur {

	@Override
	public void visiteFichier(Fichier f) {
		
		System.out.println(f.getContenu());
	}

	@Override
	public void visiteDossier(Dossier d) {
		
		System.out.println("Visite du dossier " + d.getNom() + " :\n");
		
		for(Fichiers f : d){
			
			System.out.println("\t" + f.getNom());
		}
	}
}
