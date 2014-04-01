import java.util.List;
import java.util.Collections;


public class TriJava implements StrategieTri {

	private static TriJava tri = null;
	
	public static TriJava getInstance(){
	
		if(tri == null){
		
			tri = new TriJava();
		}
		
		return tri;
	}
	
	@Override
	public <T extends Comparable<T>> List<T> trie(List<T> donnees) {
		
		Collections.sort(donnees)	;
		return donnees;
	}

	private TriJava(){
	
	}
}
