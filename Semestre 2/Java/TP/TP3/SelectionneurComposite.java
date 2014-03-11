/**
 * Selectionneur chargé d'appliquer les tests de plusieurs sélectionneurs afin de tester un fichier
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 10:29:06 CET 2014
*
*/

import java.util.*;

public class SelectionneurComposite implements Selectionneur{

	private List lstSelect;

	public SelectionneurComposite(){

		lstSelect = new LinkedList();
	}

	public void add(Selectionneur s){

		lstSelect.add(s);
	}

	/**
	 *Méthode sélectionnant un fichier si celui-ci répond au critères de sélection de la liste des selectionneurs
	 *@see Document
	 *@see Selectionneur
	 *@param d Le document à tester
	 *@return Un booléen symbolisant le résultat du test
	*/
	public boolean estSatisfaitPar(Document d){

		Iterator it = lstSelect.iterator();

		while(it.hasNext()){

			if(!((Selectionneur)it.next()).estSatisfaitPar(d)){

				return false;
			}
		}

		return true;
	}
}