import java.util.Date;
import java.util.Comparator;

public class ComparateurPersonnePrenom implements Comparator<Personne>{

	public int compare(Personne p1, Personne p2) {
 
		String n1 = p1.getPrenom();
		String n2 = p2.getPrenom();
		
		return n1.compareToIgnoreCase(n2);
	}
}
