import java.util.*;

class Texte{

	private String leTexte;
	
	public Texte(String t){
	
		leTexte = t;
	}
	
	public void afficheOccurences(CompteurOccurences c){
		
		Map m = c.calculOccurences(this);
		Iterator i = m.keySet().iterator();
		
		System.out.print("\n");
		
		while(i.hasNext()){

			Object cleTemp = i.next();
			
			System.out.println( cleTemp + " [ " +  m.get(cleTemp) + " ] ");
		}
		
		System.out.print("\n");			
	}
	
	public String getTexte(){
	
		return leTexte;
	}
}
