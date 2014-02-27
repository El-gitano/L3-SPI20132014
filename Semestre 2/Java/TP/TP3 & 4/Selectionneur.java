/**
 * Interface chargée de la sélection de documents dans une Base de documents
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 09:26:42 CET 2014
* @see BaseDocuments
* @see Document
*/
public interface Selectionneur {

	/**
	 *Méthode à définir pour savoir si un document est valide auprès du Selectionneur 
	*/
	public boolean estSatisfaitPar(Document d);
}