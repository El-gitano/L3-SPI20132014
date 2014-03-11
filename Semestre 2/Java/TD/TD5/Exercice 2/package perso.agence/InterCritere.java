import java.util.ArrayList;
import java.util.Iterator;

public class InterCritere implements Critere{

	private ArrayList criteres;
	
	public InterCritere(){
	
		criteres = new ArrayList();
	}
	
	public void add(Critere c){
	
		criteres.add(c);
	}
	
	public boolean correspond(Object o){
	
		if (o instanceof Voiture){
		
			Iterator i = criteres.iterator();
		
			while(i.hasNext()){
		
				if(! ((Critere)i.next()).correspond((Voiture)o)){
			
					return false;
				}
			}
		
			return true;
		}
		else{
		
			return false;
		}
	}
}
