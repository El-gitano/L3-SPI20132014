import java.util.LinkedList;
import java.util.List;
import java.util.Comparator;
import java.util.Collections;

class ArbreBinaireRecherche<E extends Comparable<E>>{

	private E racine;
	private ArbreBinaireRecherche<E> fg = null;
	private ArbreBinaireRecherche<E> fd = null;
	
	public ArbreBinaireRecherche(E rac){
	
		racine = rac;
	}
	
	public ArbreBinaireRecherche(E rac, ArbreBinaireRecherche<E> fg, ArbreBinaireRecherche<E> fd){
	
		racine = rac;
		this.fg = fg;
		this.fd = fd;
	}
	
	public E valeur(){
	
		return racine;
	}
	
	public ArbreBinaireRecherche filsGauche(){
	
		return fg;
	}
	
	public ArbreBinaireRecherche filsDroit(){
	
		return fd;
	}
	
	public void affecterFilsGauche(ArbreBinaireRecherche<E> el){
	
		fg = el;
	}
	
	public void affecterFilsDroit(ArbreBinaireRecherche<E> el){
	
		fd = el;
	}
	
	public boolean existeFilsDroit(){
	
		return (fd != null);
	}
	
	public boolean existeFilsGauche(){
	
		return (fg != null);
	}
	
	public boolean estFeuille(){
	
		return (!existeFilsDroit() && !existeFilsGauche());
	}
	
	public boolean contient(E element){
	
		if(racine.equals(element) || (existeFilsGauche() && fg.contient(element)) || (existeFilsDroit() && fd.contient(element) )){	
		
			return true;
			
		}
		else{
		
			return false;
		}
	}
	
	public void inserer(E element) throws DoublonException{
	
		if(contient(element)){
		
			throw new DoublonException("Il y a déjà la valeur " + element + " dans l'arbre");
		}
		else{
		
			int comparaison = racine.compareTo(element);
			
			if(comparaison > 0){
			
				if(existeFilsGauche()){
				
					fg.inserer(element);
				}
				else{
				
					fg = new ArbreBinaireRecherche<E>(element);
				}
			}	
			else{//Comparaison < 0
			
				if(existeFilsDroit()){
				
					fd.inserer(element);
				}
				else{
				
					fd = new ArbreBinaireRecherche<E>(element);
				}
			}
		}
	}
	
	public int profondeur(){
	
		return profondeur(0);
	}
	
	private int profondeur(int nb){
	
		if(estFeuille()){
		
			return nb;
		}
		else{
		
			if(existeFilsGauche() && existeFilsDroit()){
			
				return Math.max(fg.profondeur(nb+1), fd.profondeur(nb+1));
				
			}
			else if(existeFilsGauche()){
			
				return fg.profondeur(nb+1);
				
			}
			else if(existeFilsDroit()){
			
				return fd.profondeur(nb+1);
				
			}
		}
		
		return 0;//Pour que le compilateur soit ok
	}
	
	public void afficherRacine(int nbTab){
	
		for(int i = 0; i<nbTab ; i++){	
		
			System.out.print("\t");
		}
		
		System.out.print(racine + "\n");
	}
	
	public void afficherInfixe(){
	
		afficherInfixe(0);
	}
	
	private void afficherInfixe(int nb){
	
		if(existeFilsGauche()){
		
			fg.afficherInfixe(nb+1);
			
			for(int i=0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fg");
		}
		
		afficherRacine(nb);
		
		if(existeFilsDroit()){
			
			for(int i=0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fd");
			
			fd.afficherInfixe(nb+1);
		}
	}
	
	public void afficherPostfixe(){
	
		afficherPostfixe(0);
	}
	
	private void afficherPostfixe(int nb){
		
		if(existeFilsGauche()){
		
			fg.afficherPostfixe(nb+1);
			
			for(int i=0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fg");
		}
		
		if(existeFilsDroit()){
		
			fd.afficherPostfixe(nb+1);
			
			for(int i =0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fd");
		}
		
		afficherRacine(nb);
	}
	
	public void afficherPrefixe(){
	
		afficherPrefixe(0);
	}
	
	private void afficherPrefixe(int nb){
		
		afficherRacine(nb);
		
		if(existeFilsGauche()){
			
			for(int i =0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fg");
			
			fg.afficherPrefixe(nb+1);
		}
		
		if(existeFilsDroit()){
			
			for(int i =0; i<nb; i++){
			
				System.out.print("\t");
			}
			
			System.out.println("|fd");
			fd.afficherPrefixe(nb+1);
		}
	}
	
	public List<E> listElem(){
	
		List<E> elements = new LinkedList<E>();
		
		if(existeFilsGauche()){
		
			elements.addAll(fg.listElem());
		}
		
		elements.add(racine);
		
		if(existeFilsDroit()){
		
			elements.addAll(fd.listElem());
		}
		
		return elements;
	}
	
	public void afficherDepuisListe(){
	
		for(E i : listElem()){
			
				System.out.println(i + " ");
		}
	}
	
	public void afficherDepuisListe(Comparator<E> c){
	
		List<E> l = listElem();
		Collections.sort(l, c);
		
		for(E i : l){
			
				System.out.println(i + " ");
		}
	}
}
