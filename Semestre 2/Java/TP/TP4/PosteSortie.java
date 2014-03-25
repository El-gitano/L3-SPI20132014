/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 10:33:08 CET 2014
* Cette classe défini un poste de travail situé à la fin de la chaine d'usinage
* @see PosteTravailAbstrait
* @see ChaineUsinage
*/

import java.util.List;
import java.util.LinkedList;

public class PosteSortie implements Poste{

	private List<Piece> attentes;

	/**
	 * 
	 * NOTE :Le poste de sortie ne possède pas de poste suivant
	*/
	public PosteSortie(){

		attentes = new LinkedList<Piece>();
	}

	/**
	 * Ajoute la pièce à la liste du poste
	 */
	public void traiter(int date, Piece piece){

		attentes.add(piece);
	}

	/**
	 * Calcule et affiche le nombre de pièces produites, le temps d'attente max. et moyen
	 */
	public void printStat(){

		int attMax = 0;
		int attMoy = 0;

		for(Piece p : attentes){

			if(p.attente() > attMax){

				attMax = p.attente();
			}

			attMoy += p.attente();
		}

		attMoy /= attentes.size();

		System.out.print("Sortie : " + attentes.size());
		
		if(attentes.size() != 0){

			System.out.println(" pièces traitées ; Attente max = " +  attMax + ", Moyenne = " + attMoy );
		}

		System.out.print("\n");
	}
}