public class Test{

	public static void main(String [] args){
	
		CompteurOccurencesCar c = new CompteurOccurencesCar();
		CompteurOccurencesMot c2 = new CompteurOccurencesMot();
		Texte t = new Texte("Le test de la mort de la mort le test");
		
		t.afficheOccurences(c);
		t.afficheOccurences(c2);
	}
}
