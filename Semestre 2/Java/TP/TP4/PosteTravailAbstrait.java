/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 10:13:35 CET 2014
* Cette classe abstraite décrit le comportement général des postes de travail
*/
public abstract class PosteTravailAbstrait{

	private static int nbPostesTravail = 0;

	/**
	 * Variables nécessaires au chainage des postes et à l'organisation "temporelle"
	 */
	protected Echeancier echeancier;
	protected Poste pSuivant;

	/**
	 * Statistiques d'un poste et variables internes
	 */
	protected int nbPiecesTraitees;
	protected int activite;
	protected int inactivite;
	protected int numPosteTravail;
	protected int dateDerniereSortie;

	/**Chaque poste de travail nécessite un échéancier ainsi qu'un poste suivant
	* @see Echeancier
	*/
	protected PosteTravailAbstrait(Echeancier e, Poste posteSuivant){

		echeancier = e;
		pSuivant = posteSuivant;
		numPosteTravail = ++nbPostesTravail;
		
		nbPiecesTraitees = 0;
		activite = 0;
		inactivite = 0;
		dateDerniereSortie = -1;
	}

	/**
	 * @return	Une chaine répertoriant les différentes statistiques du poste
	 */
	public String getStat(){

		return new String("Nb pieces traitees = " + nbPiecesTraitees + ", Activité = " + activite + ", Inactivité = " + inactivite + "\n");
	}

	public String toString(){

		return "Poste n°" + numPosteTravail;
	}
}