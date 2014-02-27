import java.util.LinkedList;
import java.util.List;
import java.util.Iterator;

public class Agence{

	private List voitures;
	
	public Agence(){
	
		voitures = new LinkedList();
	}
	
	public void add(Voiture v){
	
		voitures.add(v);
	}
	
	public List selectionne(Critere c){
	
		Iterator i = voitures.iterator();
		LinkedList resultat = new LinkedList();
		
		while(i.hasNext()){
		
			Voiture voitTemp = (Voiture)i.next();
			
			if(c.correspond(voitTemp)){
			
				resultat.add(voitTemp);
			}
		}
		
		return resultat;
	}
}
