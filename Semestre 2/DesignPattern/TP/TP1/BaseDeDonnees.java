import java.util.List;
import java.util.LinkedList;

public class BaseDeDonnees<T extends Comparable<T>> {

	StrategieTri st;
	List<T> donnees;
	
	public BaseDeDonnees(StrategieTri s){
		
		st = s;
		donnees = new LinkedList<T>();
	}
	
	public void afficheDonneesTriees(){
		
		for(T element : st.trie(donnees)){
			
			System.out.println(element);
		}
	}
	
	public void afficheDonneesnonTriees(){
		
		for(T element : donnees){
			
			System.out.println(element);
		}
	}
	
	public void ajouter(T el){
		
		donnees.add(el);
	}
}
