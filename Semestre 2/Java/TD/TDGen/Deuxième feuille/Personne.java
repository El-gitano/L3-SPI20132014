import java.util.Date;
import java.util.Comparator;

class Personne implements Comparable<Personne>{

	protected String nom;
	protected String prenom;
	protected Date dateNaiss;
	
	public Personne(String no, String pre, Date d){
	
		nom = no;
		prenom = pre;
		dateNaiss = d;
	}
	
	public int compareTo(Personne p){
	
		return nom.compareTo(p.getNom());
	}
	
	public String getPrenom(){
	
		return prenom;
	}
	
	public Date getAge(){
	
		return dateNaiss;
	}
	
	public String getNom(){
	
		return nom;
	}
	
	public String toString(){
	
		return (nom + " " + prenom + " - " + dateNaiss);
	}
}
