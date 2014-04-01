import java.util.Date;
import java.util.Iterator;

/**
 * Cette classe représente un fichier ainsi que ses caractéristiques et son contenu
 * @author Antoine Foucault
 * 
 */
public class Fichier implements Fichiers {

		private String nom;
		private int taille;
		private Date dateCreation;
		private String contenu;
	
		/**
		 * Déclaration d'un fichier à l'aide de son nom, sa taille et son contenu
		 * @param n - Le nom
		 * @param t - La taille
		 * @param c - Le contenu
		 */
		public Fichier(String n, int t, String c){
			
			nom = n;
			taille = t;
			dateCreation = new Date();
			contenu = c;
		}
		
		/**
		 * @return La taille du fichier
		 */
		public int getTaille(){
			
			return taille;
		}
		
		/**
		 * @return Le nom du fichier
		 */
		public String getNom(){
			
			return nom;
		}
		
		/**
		 * @return La date de création du fichier
		 */
		public Date getDate(){
			
			return dateCreation;
		}
		
		/**
		 * @return Le contenu du fichier
		 */
		public String getContenu(){
			
			return contenu;
		}
		
		public Iterator<Fichiers> iterator(){
			
			return new IterateurNul();
		}
		
		private class IterateurNul implements Iterator<Fichiers>{
			
			public boolean hasNext(){
				
				return false;
			}
				
			public Fichiers next(){
					
				return null;
			}
				
			public void remove(){}
		}
		
		public String toString(){
			
			return (nom + " (" + taille + ")" + " - " + dateCreation);
		}
		
		/**
		 * Permet au fichier d'accepter un visiteur afin de lui laisser la responsabilité d'affichage et traitement de ses informations
		 * @param v - Le visiteur implémentant l'interface Visiteur
		 * @see Visiteur
		 * @see VisiteurConcretA
		 * @see VisiteurConcretB
		 */
		public void accepte(Visiteur v){
			
			v.visiteFichier(this);
		}
}
