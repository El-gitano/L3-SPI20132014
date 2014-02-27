public class CriterePrix implements Critere{

	private int prix;
	
	public CriterePrix(int prix){
	
		this.prix = prix;
	}
	
	public boolean correspond(Object o){
	
		return ( (o instanceof Voiture) && (((Voiture)o).getPrix() < prix) );
	}
}
