/**
* Cette classe décrit une date à l'aide du jour, du mois et de l'année
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 08:56:05 CET 2014
*
*/
public class Date implements Comparable{

	private int jour;
	private int mois;
	private int annee;

	/**
	 * Constructeur de la classe date
	 * @exception InvalidDateException Si le jour ou le mois est incorrect
	 */
	public Date(int jour, int mois, int annee) throws InvalidDateException{

		//On vérifie que les paramètres sont corrects
		if( (jour > 0 && jour < 32) && (mois > 0 && mois < 13)){

			this.jour = jour;
			this.mois = mois;
			this.annee = annee;
		}
		else{
			
			//Lancer l'exception du jour
			if(!(jour > 0 && jour < 32)){
				
				throw new InvalidDateException("Paramètre jour invalide (doit être compris entre 1 et 31)");
			}
			//Sinon du mois
			else{

				throw new InvalidDateException("Paramètre mois invalide (doit être compris entre 1 et 12)");
			}
		}
	}

	public int getAnnee(){

		return this.annee;
	}

	public int getMois(){

		return this.mois;
	}

	public int getJour(){

		return this.jour;
	}

	public void setAnnee(int a){

		this.annee = a;
	}

	public void setMois(int m){

		this.mois = m;
	}

	public void setJour(int j){

		this.jour = j;
	}

	public String toString(){

		return (jour + "/" + mois + "/" + annee);
	}
	
	public int compareTo(Object o){

		Date d = (Date) o;

		//Variables résultat des comparaisons successives
		int compAnnee = this.annee - d.getAnnee();
		int compMois = this.mois - d.getMois();
		int compJour = this.jour - d.getJour();

		//Retour des différents résultats possibles
		if(compAnnee != 0){

			return compAnnee;
		}
		else if(compMois != 0){

			return compMois;
		}
		else if(compJour != 0){

			return compJour;
		}
		else{

			return 0;
		}
	}

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
		Date d = (Date) o;

		return ((jour == d.getJour()) && (mois == d.getMois()) && (annee == d.getAnnee()));
	}
}
