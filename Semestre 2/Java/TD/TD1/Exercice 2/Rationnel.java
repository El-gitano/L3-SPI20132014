import java.util.ArrayList;

public class Rationnel{

	private int n;
	private int d;
	
	public static void main(String[] args){
	
		Rationnel a = new Rationnel(1, 2);
		Rationnel b = new Rationnel(2, 3);
		
		a.affiche();
		b.affiche();
		
		System.out.println(a.toDouble());
		System.out.println(b.toDouble());
		
		Rationnel c = a.somme(b);
		c.affiche();
		
		Rationnel d = a.difference(b);
		d.affiche();
		
		Rationnel e = a.produit(b);
		e.affiche();
		
		Rationnel f = a.quotient(b);
		f.affiche();
		
		System.out.println(a.compareTo(b));
		System.out.println(b.compareTo(a));
		System.out.println(a.compareTo(a));
		
		d.abs().affiche();
		
		Rationnel[] tab = Rationnel.systeme(4, 2, 3, 1, 3, 6);
		
		if(tab != null){
		
			tab[0].affiche();
			tab[1].affiche();
		}
		
		Rationnel[] tabMoy = new Rationnel[4];
		tabMoy[0] = new Rationnel(2, 1);
		tabMoy[1] = new Rationnel(4, 1);
		tabMoy[2] = new Rationnel(8, 1);
		tabMoy[3] = new Rationnel(0, 1);
		
		Rationnel.moyenne(tabMoy).affiche();
		
		System.out.println("\n");
		Rationnel racine = Rationnel.sqrt(new Rationnel(2, 1), new Rationnel(1, 500));		
		racine.affiche();
		System.out.println(racine.toDouble());
	}
	
	public Rationnel(int n, int d){
		
		this.n = n;
		this.d = d;	
		
		this.simplifier();
	}
	
	public Rationnel(Rationnel r, int d){
		
		Rationnel temp = r.quotient(new Rationnel(d, 1));
		
		this.n = temp.num();
		this.d = temp.den();
	}
	
	public Rationnel(int n, Rationnel r){
		
		Rationnel temp = new Rationnel(n, 1).quotient(r);
		
		this.n = temp.num();
		this.d = temp.den();	
	}
	
	public Rationnel(Rationnel r1, Rationnel r2){
		
		Rationnel temp = r1.quotient(r2);
		
		this.n = temp.num();
		this.d = temp.den();	
	}
	
	public int num(){
	
		return this.n;
	}
	
	public int den(){
	
		return this.d;
	}
	
	public double toDouble(){
	
		return (double)n/(double)d;
	}
	
	public Rationnel somme(Rationnel r){
	
		return ( new Rationnel( (this.n*r.den() + r.num()*this.d) , (this.d*r.den()) ) );
	}
	
	public Rationnel difference(Rationnel r){
	
		return ( new Rationnel( (this.n*r.den() - r.num()*this.d) , (this.d*r.den()) ) );
	}
	
	public Rationnel produit(Rationnel r){
	
		return ( new Rationnel( (this.n*r.num()) , (this.d*r.den()) ) );
	}
	
	public Rationnel quotient(Rationnel r){
	
		return ( new Rationnel( (this.n*r.den()) , (this.d*r.num()) ) );
	}
		
	public int compareTo(Rationnel r){
	
		return this.difference(r).num();
	}
	
	public Rationnel abs(){
	
		return new Rationnel(Math.abs(this.n), Math.abs(this.d));
	}
	
	public static Rationnel moyenne(Rationnel[] t){
	
		Rationnel res = new Rationnel(0, 1);
		int i;
		
		//On fait la somme des éléments		
		for( i=0; i < t.length; i++){
		
			res = res.somme(t[i]);
		}
		
		//On divise par le nombre d'éléments
		return (res.quotient(new Rationnel(t.length, 1)));
	}
	
	public static Rationnel[] systeme(int a, int b, int c, int d, int e, int f){
	
		int determinant = a*e - b*d;
		Rationnel[] res = null;
		
		//Une seule solution
		if(determinant != 0){
			
			res = new Rationnel[2];
			
			res[0] = new Rationnel(b*f - c*e, determinant);//Solution x
			res[1] = new Rationnel(c*d - a*f, determinant);//Solution y
		}
		
		return res;
	}
	
	public static Rationnel sqrt(Rationnel r, Rationnel precision){
		
		Rationnel uAncien = null;
		Rationnel uNouveau = new Rationnel(r, 2);
		Rationnel uTemp = null;
		Rationnel diff;
		
		do{
			
			uAncien = uNouveau;
			uNouveau = new Rationnel(1, 2).produit(uAncien.somme(r.quotient(uAncien)));	
				
		}while(precision.compareTo(uAncien.difference(uNouveau).abs()) <= 0);
		
		return uNouveau;
	}
	
	private void simplifier(){
	
		//Listes servant à la simplification
		ArrayList<Integer> lNum = new ArrayList<Integer>();
		ArrayList<Integer> lDen = new ArrayList<Integer>();
		ArrayList<Integer> lCommun = new ArrayList<Integer>();
		
		int i, divMax = 0;
		
		//Si le numérateur est égal à 0 inutile de simplifier
		if(this.n != 0){
		
			//Liste des diviseurs du numérateur	
			for(i = Math.abs(this.n); i!= 0; i--){
		
				if( (this.n % i) == 0){
			
					lNum.add(i);
				}
			}
		
			//Liste des diviseurs du dénominateur
			for(i = Math.abs(this.d); i!= 0; i--){
		
				if( (this.d % i) == 0){
			
					lDen.add(i);
				}
			}

			//Diviseurs communs
			for(i=0; i < lNum.size(); i++){
		
				if (lDen.contains(lNum.get(i))){
			
					lCommun.add(lNum.get(i));
				}
			}
		
			//Diviseur commun max.
			for(i=0; i < lCommun.size(); i++){
		
				if(lCommun.get(i) > divMax){
			
					divMax = lCommun.get(i);
				}
			}
		
			//Modifications du nombre
			this.n = this.n/divMax;
			this.d = this.d/divMax;
		}
	}
	
	public void affiche(){
	
		System.out.println(this.n + "/" + this.d);
	}
}
