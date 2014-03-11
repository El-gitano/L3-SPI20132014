import java.util.ArrayList;
import java.util.List;

class Tas{

	protected ArrayList tas;
	
	public Tas(){
	
		tas = new ArrayList();
	}
	
	public void ajouter(Carte c){
	
		tas.add(c);
	}
	
	public Carte retirer(){
	
		if(!tas.isEmpty()){
		
			return (Carte)tas.remove(0);
		}
		else{
		
			return null;
		}
	}
	
	public boolean estVide(){
	
		return tas.isEmpty();
	}
	
	public ArrayList getTas(){
	
		return tas;
	}
}
