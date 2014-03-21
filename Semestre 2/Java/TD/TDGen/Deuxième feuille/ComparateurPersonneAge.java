import java.util.Date;
import java.util.Comparator;

public class ComparateurPersonneAge implements Comparator<Personne>{

	public int compare(Personne p1, Personne p2) {
 
		Date d1 = p1.getAge();
		Date d2 = p2.getAge();
		
		return d1.compareTo(d2);
	}
}
