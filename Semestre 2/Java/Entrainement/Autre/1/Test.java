public class Test{

	public static void main(String[] args){
	
		System.out.println("Début du programme\n");
		
		/*Test du polymorphisme ad-hoc (type des paramètres)*/
		methode("hello");
		methode(1);
		methode(true);
		
		System.out.println("\n");
		
		//Test sur l'héritage
		Prems a = new Prems();
		Deuxs b = new Deuxs();
		
		a.maMeth();
		b.maMeth();
		b.maMethperso();
		
		System.out.println("\n");
		
		//Test sur le polymorphisme d'héritage & .co
		Autre c = new Autre();
		Autre d = new Autre("Une autre phrase");
		Autre e = new Autre("Première phrase", "Deuxième phrase");
		
		c.afficheToi();
		d.afficheToi();
		e.afficheToi();
		
		System.out.println("\n");
		
		//Test sur la redéfinition
		a.afficheAttributs();
		b.afficheAttributs();
		
		System.out.println("\n");
		
		//Test upcasting		
		a.toString();
		b.toString();
		
		Prems f = b; //Upcasting
		f.toString();	
		
		System.exit(0);	
	}
	
	/*Méthodes crées pour voir le polymorphisme de type*/
	private static void methode(String s){
	
		System.out.println("Une chaîne");
	}
	
	private static void methode(Integer i){
	
		System.out.println("Un nombre");
	}
	
	private static void methode(Boolean b){
	
		System.out.println("Un booléen");
	}
}

/*Test de l'héritage et du polymorphisme d'héritage*/
class Prems{

	/*Déclaration des var. d'intance en "protected" pour autoriser l'accès aux classes filles*/
	protected int x;
	protected int y;
	
	public void maMeth(){
	
		System.out.println("Une classe prems");
	}
	
	public void maMethperso(){
	
		System.out.println("Méthode d'une prem's");
	}
	
	/*Ajouter "final" pour être sur que cette méthode est appelée lors de la liaison dynamique (on part de la classe mère et on descend le plus bas possible dans l'arborescence tant qu'on rencontre une redéfinition de cette méthode sauf si on rencontre "final" -> execution de cette méthode)*/
	public void afficheAttributs(){
	
		System.out.println(this.x + " et " + this.y);
	}
	
	public Prems(){
	
		this.x = 33;
		this.y = 66;
	}
	
	public void toString(){
	
		System.out.println("["+this.x+", "+this.y+"]");
	}
}

class Deuxs extends Prems{
	
	/*Pas de classe fille, on met en "private*/
	private int z;
	
	public Deuxs(){
	
		super();
		this.x = 22;
		this.z = 99;
	}
	
	public void maMeth(){
	
		System.out.println("Une classe deuxs");
	}
	
	public void afficheAttributs(){
	
		super.afficheAttributs();
		System.out.println(" et " + this.z);
	}
	
	public void toString(){
		super.toString();
		System.out.println("["+this.z+"]");
	}
}

/*Test des constructeurs*/
class Autre{

	private String s;
	private String s2;
	
	public Autre(String phrase, String phrase2){
	
		this(phrase);
		this.s2 = new String(phrase2);
	}
	
	public Autre(String phrase){
	
		this.s = new String(phrase);
	}
	
	public Autre(){
	
		this.s = new String("Phrase par défaut");
	}
	
	public void afficheToi(){
	
		System.out.println(this.s);
		
		if(s2 != null){
		
			System.out.println(this.s2);
		}
	}
}
