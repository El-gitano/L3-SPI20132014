import java.util.Random;

public class EnsembleDeChiffres{

	private boolean[] present;
	
	public static void main(String[] args){
	
		EnsembleDeChiffres a = new EnsembleDeChiffres();
		EnsembleDeChiffres b = new EnsembleDeChiffres();
		
		a.tirerAuHasard();
		b.tirerAuHasard();
		
		a.affiche();
		b.affiche();
		System.out.println("\n");
		
		EnsembleDeChiffres c = a.intersectionAvec(b);
		EnsembleDeChiffres d = a.unionAvec(b);
		
		c.affiche();
		d.affiche();
		System.out.println("\n");
		
		EnsembleDeChiffres e = new EnsembleDeChiffres();
		EnsembleDeChiffres f = new EnsembleDeChiffres();
		
		f.ajoute(5);
		f.ajoute(7);
		
		e.ajoute(5);
		
		System.out.println(e.estInclusDans(f));
		System.out.println(f.estInclusDans(e));
		
		System.exit(0);
	}
	
	public EnsembleDeChiffres(){
	
		int i;
		
		present = new boolean[10];
		
		for(i = 0; i < present.length; i++){
		
			present[i] = false;
		}
	}
	
	public void ajoute(int i){
	
		this.present[i] = true;
	}
	
	public void retire(int i){
	
		this.present[i] = false;
	}
	
	public void tirerAuHasard(){
	
		Random rand = new Random();
		int i;
		
		for(i = 0; i < present.length; i++){
					
			present[i] = rand.nextBoolean();
		}
	}
	
	public boolean appartient(int i){
	
		return this.present[i];
	}
	
	public EnsembleDeChiffres intersectionAvec(EnsembleDeChiffres e){
	
		EnsembleDeChiffres res = new EnsembleDeChiffres();
		int i;
		
		for(i = 0; i < present.length; i++){
					
			if(this.present[i] && e.appartient(i)){
			
				res.ajoute(i);
			}
		}
		
		return res;
	}
	
	public EnsembleDeChiffres unionAvec(EnsembleDeChiffres e){
	
		EnsembleDeChiffres res = new EnsembleDeChiffres();		
		int i;
		
		for(i = 0; i < present.length; i++){
					
			if(this.present[i] || e.appartient(i)){
			
				res.ajoute(i);
			}
		}
		
		return res;
	}
	
	public boolean estInclusDans(EnsembleDeChiffres e){
	
		boolean appartient = true;
		int i;
		
		for(i = 0; i < present.length && appartient == true; i++){
					
			if( (this.present[i] == true) && (this.present[i] != e.appartient(i)) ){
			
				appartient = false;
			}
		}
		
		return appartient;
	}
	
	public void affiche(){
	
		int i;
		
		System.out.print("{");
		
		for(i = 0; i < this.present.length; i++){
				
			if(i != this.present.length -1){
			
				System.out.print(i + "(" + this.present[i] + "), ");
			}
			else{
			
				System.out.print(i + "(" + this.present[i] + ")");
			}
		}
		
		System.out.print("}\n");
	}
}
