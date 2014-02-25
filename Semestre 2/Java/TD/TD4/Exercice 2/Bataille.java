import java.util.ArrayList;
import java.util.Scanner;
import java.util.Iterator;

class Bataille{

	private ArrayList joueurs;
	private PileDeCartes pile;
	
	public Bataille(){
	
		joueurs = new ArrayList();
		pile = new PileDeCartes();
		
		String [] couleurs = {"carreau", "trèfle", "pique", "coeur"};
		Scanner s = new Scanner(System.in);
		int i, j;
		
		//Création du jeu de cartes
		for(i=0; i < couleurs.length; i++){
		
			Couleur cTemp = new Couleur(couleurs[i]);
			
			for(j=1; j<= 13; j++){
			
				pile.ajouter(new Carte(cTemp, new Valeur(j)));
			}
		}
		
		//Création des joueurs
		for(i=0; i < 2; i++){
		
			System.out.print("\nVeuillez entrer le nom du joueur " + (i+1) + " : ");
			String nomJoueur = s.nextLine();
			joueurs.add(new Joueur(nomJoueur));
		}
		
		//Mélange du paquet
		pile.melanger();
		
		//Distribution
		for(i=0; !pile.estVide(); i++){
		
			((Joueur)joueurs.get(i%2)).getPaquet().ajouter(pile.retirer());
		}
	}
	
	public void lancerJeu(){
	
		Joueur gagnant = gagnant();
		
		while(gagnant == null){
		
			try{
				Thread.sleep(1000);
			}
			catch(Exception e){
			
				System.out.println(e);
			}
			
			Carte c1 = ((Joueur)joueurs.get(0)).getPaquet().retirer();
			Carte c2 = ((Joueur)joueurs.get(1)).getPaquet().retirer();
			
			pile.ajouter(c1);
			pile.ajouter(c2);
			
			System.out.println((Joueur)joueurs.get(0) + " a joué la carte " + c1);
			System.out.println((Joueur)joueurs.get(1) + " a joué la carte " + c2);
				
			//Joueur 1 gagne
			if(c1.compareTo(c2) > 0){
				
				System.out.println("Joueur 1 gagne la manche et ramasse le tas\n");
				pile.melanger();
				((Joueur)joueurs.get(0)).ramasserTas(pile);
			}
			//Joueur 2 gagne
			else if(c1.compareTo(c2) < 0){
			
				System.out.println("Joueur 2 gagne la manche et ramasse le tas\n");
				pile.melanger();
				((Joueur)joueurs.get(1)).ramasserTas(pile);
			}
			else{
			
				System.out.println("Égalité !\n");
			}
			
			gagnant = gagnant();
		}
		
		System.out.println("Le gagnant est : " + gagnant);
	}
	
	private Joueur gagnant(){
	
		Iterator it = joueurs.iterator();
		Joueur gagnant = null, jTemp;
		int cpt = 0;
		
		while(it.hasNext()){
			
			jTemp = (Joueur)it.next();
			
			if(!jTemp.estElimine()){
			
				gagnant = jTemp;
				cpt += 1;
			}
		}
		
		if(cpt == 1){
		
			return gagnant;
		}
		else{
		
			return null;
		}
	}
}
