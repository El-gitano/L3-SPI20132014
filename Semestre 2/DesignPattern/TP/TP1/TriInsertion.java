import java.util.List;
import java.util.LinkedList;


public class TriInsertion implements StrategieTri {
	
	@Override
	public <T extends Comparable<T>> List<T> trie(List<T> donnees) {
		
		List<T> resultat = new LinkedList<T>();
		int i;
		boolean insertion;
		
		for(T element : donnees){
			
			for(i=0, insertion=false; i < resultat.size(); i++){
				
				if(element.compareTo(resultat.get(i)) < 0){
					
					resultat.add(i, element);
					insertion = true;
				}
			}
			
			//Dans le cas où l'élément est plus grand que tous les autres
			if(!insertion){
				
				resultat.add(element);
			}
		}
		
		return resultat;
	}

}
