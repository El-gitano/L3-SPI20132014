import java.util.*;

public class CompteurOccurencesMot implements CompteurOccurences{

	public Map calculOccurences(Texte t){
	
		Map resultat = new HashMap();
		int i;
		String [] mots = t.getTexte().split("[\\s., ;:!?]");
		
		for(i=0; i < mots.length; i++){
		
			String c = mots[i];
			
			if(resultat.containsKey(c)){
			
				resultat.put(c, (int)resultat.get(c)+1);
			}
			else{
				
				resultat.put(c, 1);
			}
		}
		
		return resultat;
	}
}
