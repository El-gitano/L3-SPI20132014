import java.util.Date;
import java.util.List;
import java.util.Stack;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Iterator;

/**
 * La classe dossier contient des fichiers stockés dans une liste chaînée
 * @author Antoine Foucault
 *
 */
public class Dossier implements Fichiers{

	private String nom;
	private List<Fichiers> lstFichiers;
	private int taille;
	private Date dateCreation;
	
	/**
	 * Construit un dossier vide à partir de son nom
	 * @param n - Le nom du dossier
	 */
	public Dossier(String n){
		
		nom = n;
		taille = 0;
		dateCreation = new Date();
		lstFichiers = new LinkedList<Fichiers>();
	}
	
	/**
	 * Construit un dossier à partir de son nom et d'un tableau de Fichiers
	 * @param n - Le nom du dossier
	 * @param lstFich Le tableau de fichiers
	 * @see Fichiers
	 */
	public Dossier(String n, Fichiers[] lstFich){
		
		this(n);
		lstFichiers.addAll(Arrays.asList(lstFich));
		taille = getTaille();
	}
	
	/**
	 * Construit un dossier à partir de son nom et d'un Fichiers
	 * @param n - Le nom du dossier
	 * @param lstFich Le Fichiers
	 * @see Fichiers
	 */
	public Dossier(String n, Fichiers f){
		
		this(n);
		lstFichiers.add(f);
		taille = getTaille();
	}
	
	/**
	 * Cette méthode permet d'ajouter un ensemble de Fichiers au dossier
	 * @param f Un ou plusieurs fichiers
	 * @see Fichiers
	 */
	public void add(Fichiers ... f){
		
		lstFichiers.addAll(Arrays.asList(f));
		taille = getTaille();
	}
	
	/**
	 * @return La taille du dossier (la taille de l'ensemble des fichiers qu'il contient)
	 */
	@Override
	public int getTaille() {
		
		int taille = 0;
		
		for(Fichiers f : lstFichiers){
			
			taille += f.getTaille();
		}
		
		return taille;
	}

	/**
	 * @return La date de création du dossier
	 */
	public Date getDate(){
		
		return dateCreation;
	}
	
	/**
	 * @return Le nom du dossier
	 */
	@Override
	public String getNom() {
		
		return nom;
	}
	
	/**
	 * @return Un itérateur sur tous les fichiers contenus par le dossier et ses sous-dossiers
	 */
	public Iterator<Fichiers> iterator(){
		
		return new IterateurDossier();
	}
	
	private class IterateurDossier implements Iterator<Fichiers>{
		
		private Stack<Iterator<Fichiers>> pileIterateurs;
		private Iterator<Fichiers> iterateurLocal;
		
		public IterateurDossier(){
			
			iterateurLocal = lstFichiers.iterator();
			pileIterateurs = new Stack<Iterator<Fichiers>>();
		}
		
		public boolean hasNext(){
			
			//On supprime les itérateurs qui n'ont plus rien à fournir
			while(!pileIterateurs.empty() && !pileIterateurs.peek().hasNext()){
			
				pileIterateurs.pop();
			}
			
			//On retourne vrai s'il reste un itérateur valide dans la pile
			if(!pileIterateurs.empty()){
				
				return true;
			}
			else{
				
				return (iterateurLocal.hasNext());
			}
		}
			
		public Fichiers next(){
			
			//On retourne un fichier si un itérateur le permet, sinon null
			if(!pileIterateurs.empty()){
				
				return (pileIterateurs.peek().next());
			}
			//Si on retourne dans le dossier actuel, on retourne le fichier suivant et on empile son itérateur
			else{
				
				Fichiers temp = iterateurLocal.next();
				pileIterateurs.push(temp.iterator());
				return (temp);
			}
		}
			
		public void remove(){}
	}
	
	public String toString(){
		
		return (nom + " (" + taille + ")" + " - " + dateCreation);
	}
	
	/**
	 * Permet au fdossier d'accepter un visiteur afin de lui laisser la responsabilité d'affichage et traitement de ses informations
	 * @param v - Le visiteur implémentant l'interface Visiteur
	 * @see Visiteur
	 * @see VisiteurConcretA
	 * @see VisiteurConcretB
	 */
	public void accepte(Visiteur v){
		
		v.visiteDossier(this);
	}
}
