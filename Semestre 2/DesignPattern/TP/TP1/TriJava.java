import java.util.List;
import java.util.Collections;


public class TriJava implements StrategieTri {

	@Override
	public <T extends Comparable<T>> List<T> trie(List<T> donnees) {
		
		Collections.sort(donnees)	;
		return donnees;
	}

}
