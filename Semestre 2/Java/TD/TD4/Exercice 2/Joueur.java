import java.util.ArrayList;

class Joueur{

	private Tas paquet;
	private String nom;
	
	public Joueur(String s){
	
		paquet = new Tas();
		nom = s;
	}
	
	public boolean estElimine(){
	
		return paquet.estVide();
	}
	
	public void ramasserTas(PileDeCartes p){
	
		paquet.getTas().addAll(p.getTas());
		p.vider();	
	}
	
	public Tas getPaquet(){
	
		return paquet;
	}
	
	public String toString(){
	
		return nom;
	}
}
