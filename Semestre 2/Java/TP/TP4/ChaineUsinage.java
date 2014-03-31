/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Mar 25 09:41:26 CET 2014
* Cette classe définit une chaine d'usinage ainsi que tous les composants associés à celle-ci
* @see PosteTravailAbstrait
* @see Echeancier
*/
public class ChaineUsinage {

	public static void main(String[] args) throws Exception{

		Echeancier e = new Echeancier();
		
		Poste sortie = new PosteSortie();
		Poste p3 = new PosteConstant(e, sortie, 10);
		Poste p2 = new PosteVariable(e, p3);
		Poste p1 = new PosteConstant(e, p2, 6);
		
		e.enregistrer(new Mouvement(20, new Piece(3), p1));
		e.enregistrer(new Mouvement(21, new Piece(7), p1));
		e.enregistrer(new Mouvement(22, new Piece(5), p1));

		//e.afficher();
		
		while(!e.vide()){

			Mouvement m = e.prochain();
			m.poste().traiter(m.date(), m.piece());
			//e.afficher();
		}

		System.out.print("\n");
		
		p1.printStat();

		System.out.print("\n");
	}
}