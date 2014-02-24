/**
* Cette classe décrit un document composé d'un titre et d'un auteur
* @see Auteur
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 10:44:33 CET 2014
*
*/
public class Document {

	private String titre;
	private Auteur auteur;
	private boolean emprunt;

	/**
	 * Constructeur d'une instance de la classe document
	 */
	public Document(String unTitre, Auteur unAuteur){

		titre = unTitre;
		auteur = unAuteur;
		/** Définit si le livre est emprunté*/
		emprunt = false;
	}

	public String getTitre(){

		return titre;
	}

	public Auteur getAuteur(){

		return auteur;
	}

	public boolean getEmprunt(){

		return emprunt;
	}
	
	public void setAuteur(Auteur unAuteur){

		auteur = unAuteur;
	}

	public void setTitre(String unTitre){

		titre = unTitre;
	}

	public void setEmprunt(boolean b){

		emprunt = b;
	}

	public String toString(){

		return "Titre : " + titre + "\nAuteur : \n\t" + auteur;
	}

	/** Compare le titre et l'auteur pour établir l'égalité */
	public boolean equals(Object o){

		//On effectue une "vérification générique"
		if(this == o){

			return true;
		}
		else if(o == null){

			return false;
		}
		else if(getClass() != o.getClass()){

			return false;
		}

		Document d = (Document) o;

		return (titre.equals(d.getTitre()) && auteur.equals(d.getAuteur()));
	}
}