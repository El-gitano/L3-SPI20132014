/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:19:47 CET 2014
* Cette classe décrit une pièce dédiée à etre modifiée dans une chaine d'usinage
* @see PosteTravailAbstrait
* @see ChaineUsinage
*/
public class Piece {

	private static int numPiece = 0;
	
	private int dureeTraitement;
	private int attente;
	private int numero;

	/**
	 * @param dureeTraitement	Définit le temps de traitement de cette pièce dans un poste de travail variable
	 * @see PosteVariable
	 */
	public Piece(int dureeTraitement){

		this.dureeTraitement = dureeTraitement;
		attente = 0;
		numero = numPiece++;
	}

	public int attente(){

		return attente;
	}

	/**
	 * Augmente la valeur de la variable d'instance attente
	 * @param duree 	Temps à ajouter
	 */
	public void attendre(int duree){

		attente += duree;
	}
	
	public int dureeTraitement(){

		return dureeTraitement;
	}

	public String toString(){

		return (new String("Pièce n°" + numero));
	}
}