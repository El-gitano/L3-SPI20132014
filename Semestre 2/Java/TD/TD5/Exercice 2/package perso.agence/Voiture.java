class Voiture{

	private String nom;
	private String marque;
	private int anneeProd;
	private int prixLoc;
	
	public Voiture(String marque, String nom, int anneeProd, int prixLoc){
	
		this.nom = nom;
		this.marque = marque;
		this.anneeProd = anneeProd;
		this.prixLoc = prixLoc;
	}
	
	public String getMarque(){
	
		return marque;
	}
	
	public int getPrix(){
	
		return prixLoc;
	}
	
	public String toString(){
	
		return (nom + " [ " + marque + " ] - " + anneeProd + " | " + prixLoc);
	}
}
