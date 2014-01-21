public class Test{

	public static void main(String[] args){
	
		System.out.println("Début du programme\n");
		
		methode("hello");
		methode(1);
		methode(true);
		
		System.out.println("\n");
		
		Prems a = new Prems();
		Deuxs b = new Deuxs();
		
		a.maMeth();
		b.maMeth();
		b.maMethperso();
		
		System.exit(0);	
	}
	
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

class Prems{

	public static void maMeth(){
	
		System.out.println("Une classe prems");
	}
	
	public static void maMethperso(){
	
		System.out.println("Méthode d'une prem's");
	}
}

class Deuxs extends Prems{

	public static void maMeth(){
	
		System.out.println("Une classe deuxs");
	}
}
