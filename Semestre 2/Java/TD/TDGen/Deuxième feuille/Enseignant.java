import java.util.Date;
import java.util.Comparator;

class Enseignant extends Personne{

	private EnumStatut statut;
	
	public Enseignant(String no, String pre, Date d, EnumStatut statut){
	
		super(no, pre, d);
		this.statut = statut;
	}
}
