/**
* Cette classe décrit un auteur à partir de ses dates de naissance/mort ainsi que son nom/prénom
* @see Date
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 10:20:23 CET 2014
*
*/
public class Auteur{

	private String nom;
	private String prenom;
	private Date dateNaissance;
	private Date dateMort;

	/**
	 * Constructeur d'un auteur mort
	 * Levée d'une exception InvalidAuteurException en cas de date de décès antérieure à la date de mort
	 * @exception InvalidAuteurException
	 */
	public Auteur(String nom, String prenom, Date dNaiss, Date dMort) throws InvalidAuteurException{

		//Appel au constructeur moins spécialisé
		this(nom, prenom, dNaiss);

		if(dNaiss.compareTo(dMort) < 0){

			this.dateMort = dMort;
		}
		else{

			throw new InvalidAuteurException("Date de mort antérieure à la date de naissance ( " + dNaiss + " - " + dMort + " )");
		}
			
	}

	/**
	 * Constructeur d'un auteur vivant
	 */
	public Auteur(String nom, String prenom, Date dNaiss){

		this.nom = nom;
		this.prenom = prenom;
		this.dateNaissance = dNaiss;
		this.dateMort = null;
	}

	public String getNom(){

		return nom;
	}

	public String getPrenom(){

		return prenom;
	}

	public Date getNaissance(){

		return dateNaissance;	
	}

	public Date getMort(){

		return dateMort;
	}

	public void setNom(String unNom){

		nom = unNom;
	}

	public void setPrenom(String unPrenom){

		prenom = unPrenom;
	}

	public void setNaissance(Date n){

		dateNaissance = n;
	}

	public void setMort(Date m){

		dateMort = m;
	}
	
	public String toString(){

		if(dateMort != null){
			
			return nom + " " + prenom + "( " + dateNaissance + ")";
		}
		else{

			return nom + " " + prenom + "( " + dateNaissance + " - " + dateMort + ")";
		}			
	}

	/** Compare les dates de naissance/mort ainsi que le nom pour établir l'égalité*/
	public boolean equals(Object o){

		//On effectue une "vérification générique"
		if(this == o){

			return true;
		}
		else if(o == null){

			return false;
		}
		else if(getClass() != o.getClass()){

			return false;
		}

		//On peut comparer les champs des deux objets
		Auteur a = (Auteur) o;

		//Même nom, prénom, date de naissance/mort
		if (dateMort != null){

			return (nom.equals(a.getNom()) && prenom.equals(a.getPrenom()) && dateNaissance.equals(a.getNaissance()) && dateMort.equals(a.getMort()));
		}
		else{

			return (nom.equals(a.getNom()) && prenom.equals(a.getPrenom()) && dateNaissance.equals(a.getNaissance()) && a.getMort() == null);
		}
	}
}