/**
 * Interface chargée de la sélection de documents dans une Base de documents
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 09:35:58 CET 2014
* @see Document
* @see BaseDocuments
*/
public class NonEmprunteSelectionneur implements Selectionneur{

	/**
	 *Méthode sélectionnant un fichier s'il n'est pas emprunté
	 *@see Document
	 *@param d Le document à tester
	 *@return Un booléen symbolisant le résultat du test
	*/
	public boolean estSatisfaitPar(Document d){

		if(d.getEmprunt()){

			return false;
		}
		else{

			return true;
		}
	}
}