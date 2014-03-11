public class CritereMarque implements Critere{

	private String marque;
	
	public CritereMarque(String marque){
	
		this.marque = marque;
	}
	
	public boolean correspond(Object o){
	
		return ( (o instanceof Voiture) && ( ((Voiture)o).getMarque().equals(marque) ) );
	}
}
