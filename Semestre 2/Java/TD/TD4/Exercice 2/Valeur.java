class Valeur implements Comparable{

	private int valeur;
	
	public Valeur(int i){
	
		valeur = i;
	}
	
	public int getVal(){
	
		return valeur;
	}
	
	public int compareTo(Object o){
	
		Valeur v = (Valeur) o;
		
		//Exceptions pour les as
		if( (v.getVal() == 1) && (valeur != 1)){
		
			return -1;
		}
		else if((valeur == 1) && (v.getVal() != 1)){
		
			return 1;
		}
		//Cas général
		else{
		
			return valeur - v.getVal();
		}
	}
	
	public String toString(){
		
		switch(valeur){
	
			case 1 : return "As";
			case 11 : return "Valet";
			case 12 : return "Dame";
			case 13 : return "Roi";
			default : return String.valueOf(valeur);
		}
	}
}
