/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:38:23 CET 2014
* Cette classe décrit un poste ayant un temps de travail constant
* @see PosteTravailAbstrait
*/
public class PosteConstant extends PosteTravailAbstrait implements Poste{

	private int dureeTraitement;

	/**
	 * @param duree	La durée associé à chaque traitement pour ce poste
	 */
	public PosteConstant(Echeancier e, Poste pSuiv, int duree){

		super(e, pSuiv);
		dureeTraitement = duree;	
	}

	/**
	 * Le poste traite la pièce s'il en est capable sinon il replace la pièce dans l'échéancier à la date où il estime qu'il sera capable de la traiter
	 */
	public void traiter(int date, Piece piece){

		if(dateDerniereSortie == -1){

			dateDerniereSortie = date;
		}
		
		//La pièce n'a pu etre traitée car un autre traitement était en cours		
		if(date < dateDerniereSortie){

			piece.attendre(dateDerniereSortie - date);
			echeancier.enregistrer(new Mouvement(dateDerniereSortie, piece, this));
		}
		//La pièce peut etre traitée
		else{

			//Modification des statistiques
			nbPiecesTraitees++;
			inactivite += (date - dateDerniereSortie);
			activite += dureeTraitement;
			dateDerniereSortie = date + dureeTraitement;

			//Envoi de la pièce au poste suivant
			echeancier.enregistrer(new Mouvement(dateDerniereSortie, piece, pSuivant));	
		}
	}

	/**
	 * Affiche les statistiques du poste (nombre de pièces, temps en activité/inactivité)
	 */
	public void printStat(){

		System.out.print("Travail (Constant-" + numPosteTravail + " (" + dureeTraitement + ")) : " + getStat());
		pSuivant.printStat();
	}
}