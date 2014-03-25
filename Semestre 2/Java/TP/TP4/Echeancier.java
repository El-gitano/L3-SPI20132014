/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:25:30 CET 2014
* Cette classe décrit une sorte d'ordonnanceur de mouvements dans une chaine d'usinage
* @see ChaineUsinage
* @see Mouvement
*/

import java.util.List;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Collections;



public class Echeancier {

	private List<Mouvement> lstMouvements;

	public Echeancier(){

		lstMouvements = new LinkedList<Mouvement>();
	}

	/**
	 * Retourne true si l'échancier est vide, false sinon
	 */
	public boolean vide(){

		return (lstMouvements.isEmpty());
	}

	/**
	 * Retourne le prochain mouvement de l'échéancier à devoir etre traité. Ce mouvement est retiré de l'échéancier
	 * @see Mouvement
	 */
	public Mouvement prochain() throws NoSuchElementException{

		Mouvement retour;
		
		if(vide()){

			throw new NoSuchElementException("Pas d'éléments dans l'échéancier !");
		}

		retour = lstMouvements.get(0);
		lstMouvements.remove(0);
		
		return (retour);
	}

	/**
	 * Ajoute un mouvement à l'échancier
	 * @see Mouvement
	 */
	public void enregistrer(Mouvement m){

		lstMouvements.add(m);
		Collections.sort(lstMouvements);
	}

	/**Affiche l'ensemble des mouvements contenus dans l'échéancier*/
	public void afficher(){

		System.out.print("\n");
		
		for(Mouvement m : lstMouvements){

			System.out.println(m);
		}

		System.out.print("\n");
	}
}