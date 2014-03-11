import java.util.*;

public class CompteurOccurencesCar implements CompteurOccurences{

	public Map calculOccurences(Texte t){
	
		Map resultat = new HashMap();
		int i;
		String texte = t.getTexte();
		
		for(i=0; i < texte.length(); i++){
		
			char c = texte.charAt(i);
			
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
