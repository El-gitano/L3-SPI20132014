import java.util.List;
import java.util.Collections;

public class TriBulle implements StrategieTri {

	@Override
	public <T extends Comparable<T>> List<T> trie(List<T> donnees) {
		
		boolean echange;
		int i, butee = 1;
		
		do{
			
			for(i=0, echange=false; i < (donnees.size()-butee) ; i++){
				
				if( donnees.get(i).compareTo(donnees.get(i+1)) > 0 ){
					
					Collections.swap(donnees, i, i+1);
					echange = true;
				}
			}
			
			butee++;
			
		}while(echange != false);
		
		return donnees;
	}

}
