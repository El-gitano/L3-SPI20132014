/**
 * Ce visiteur récupère le fichier le plus vieux qu'il rencontre lors du parcours d'une arborescence
 * @author Antoine Foucault
 *
 */
public class VisiteurConcretB implements Visiteur {

	Fichiers plusVieux;
	
	public void visiteFichier(Fichier f) {
		
		if((plusVieux  == null) || (plusVieux.getDate().compareTo(f.getDate()) < 0)){
			
			plusVieux = f;
		}
	}

	@Override
	public void visiteDossier(Dossier d) {
		
		if((plusVieux  == null) || (plusVieux.getDate().compareTo(d.getDate()) < 0)){
			
			plusVieux = d;
		}
	}

	public Fichiers getPlusVieux(){
		
		return plusVieux;
	}
}
