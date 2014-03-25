/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:38:35 CET 2014
* Cette classe décrit un poste ayant un temps de travail spécifique à la pièce traitée
* @see PosteTravailAbstrait
*/
public class PosteVariable extends PosteTravailAbstrait implements Poste{

	public PosteVariable(Echeancier e, Poste pSuiv){

		super(e, pSuiv);	
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

			inactivite += (date - dateDerniereSortie);
			nbPiecesTraitees++;
			activite += piece.dureeTraitement();
			dateDerniereSortie = date + piece.dureeTraitement();
			echeancier.enregistrer(new Mouvement(dateDerniereSortie, piece, pSuivant));	
		}
	}

	/**
	 * Affiche les statistiques du poste (nombre de pièces, temps en activité/inactivité)
	 */
	public void printStat(){

		System.out.print("Travail (Variable-" + numPosteTravail + ") : " + getStat());
		pSuivant.printStat();
	}
}