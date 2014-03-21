
public class CompteurDeCancans implements Cancaneur{
	
	private static int nbCancans = 0;
	Cancaneur c;
	
	public CompteurDeCancans(Cancaneur c){
		
		this.c = c;
		
		nbCancans++;
	}

	@Override
	public void cancaner() {
		
		c.cancaner();
	}

	public static int getNbCancans(){
		
		return nbCancans;
	}
	
	public static void setNbCancans(int nb){
		
		nbCancans = nb;
	}
}
