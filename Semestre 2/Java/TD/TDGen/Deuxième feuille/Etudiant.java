import java.util.Date;

class Etudiant extends Personne{

	private EnumNiveau niveau;
	
	public  Etudiant(String no, String pre, Date d, EnumNiveau niveau){
	
		super(no, pre, d);
		this.niveau = niveau;
	}
}
