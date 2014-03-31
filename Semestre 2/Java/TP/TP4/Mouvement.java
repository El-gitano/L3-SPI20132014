/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:22:02 CET 2014
* Cette classe décrit un mouvement effectué au sein de la chaine d'usinage
* @see ChaineUsinage
*/
public class Mouvement implements Comparable<Mouvement>{

	private int date;
	private Piece piece;
	private Poste poste;

	/**
	 * Dans l'implémentation actuelle un mouvement est définit par une date d'arrivée à un poste, une pièce à traiter et un poste de traitement associé
	 * @see Mouvement
	 * @see Piece
	 * @see PosteTravailAbstrait
	 */
	public Mouvement(int d, Piece pi, Poste po){

		date = d;
		piece = pi;
		poste = po;
	}
	
	public int date(){

		return date;
	}

	public Piece piece(){

		return piece;
	}

	public Poste poste(){

		return poste;
	}

	/**
	 * Il est possible de comparer les mouvements sur plusieurs critères, nous avons choisi ici la date d'arrivé dans un poste
	 */
	public int compareTo(Mouvement m){

		return (date - m.date());
	}

	public String toString(){

		return (new String(String.valueOf(date) + " - " + piece + " - " + poste));
	}
}