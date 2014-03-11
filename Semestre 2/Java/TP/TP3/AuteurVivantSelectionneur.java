/**
 * Interface chargée de la sélection de documents dans une Base de documents
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 09:38:50 CET 2014
* @see Document
* @see BaseDocuments
*/
public class AuteurVivantSelectionneur implements Selectionneur{

	private Date dateComp;

	public AuteurVivantSelectionneur(Date d){

		dateComp = d;
	}

	public Date getDate(){

		return dateComp;
	}

	public void setDate(Date d){

		dateComp = d;
	}

	/**
	 *Méthode sélectionnant un fichier si la date de mort de l'auteur est antérieure ou égale à la date de comparaison
	 *@see Document
	 *@param d Le document à tester
	 *@return Un booléen symbolisant le résultat du test
	*/
	public boolean estSatisfaitPar(Document d){

		Date mort = d.getAuteur().getMort();

		//Si l'auteur est mort et que sa mort est > à la date de comparaison 
		if( (mort != null) && (mort.compareTo(dateComp) > 0) ){

			return false;
		}
		else{

			return true;
		}
	}
}