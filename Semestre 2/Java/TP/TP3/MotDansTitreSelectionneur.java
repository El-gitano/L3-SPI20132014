/**
 * Interface chargée de la sélection de documents dans une Base de documents
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 09:46:17 CET 2014
* @see Document
* @see BaseDocuments
*/
public class MotDansTitreSelectionneur implements Selectionneur{

	private String motComp;
	
	public MotDansTitreSelectionneur(String s){

		motComp = s;
	}

	public String getMotComp(){

		return motComp;
	}

	public void setMotComp(String s){

		motComp = s;
	}

	/**
	 *Méthode sélectionnant un fichier si la date de mort de l'auteur est antérieure ou égale à la date de comparaison
	 *@see Document
	 *@param d Le document à tester
	 *@return Un booléen symbolisant le résultat du test
	*/
	public boolean estSatisfaitPar(Document d){

		if(d.getTitre().indexOf(motComp) != -1){

			return true;
		}
		else{

			return false;
		}
	}
}