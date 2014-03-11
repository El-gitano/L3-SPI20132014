class Carte implements Comparable{

	private Couleur couleur;
	private Valeur valeur;
	
	public Carte(Couleur c, Valeur v){
	
		couleur = c;
		valeur = v;
	}
	
	public int compareTo(Object o){
	
		Carte c = (Carte) o;
		
		return valeur.compareTo(c.getVal());
	}
	
	public Valeur getVal(){
	
		return valeur;
	}
	
	public String toString(){
	
		return valeur.toString() + " " + couleur.toString();
	}
}
