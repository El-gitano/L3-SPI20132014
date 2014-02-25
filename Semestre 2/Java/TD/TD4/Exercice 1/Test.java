class Test{

	public static void main(String args[]){

		try{
		
			EntierNat n1 = new EntierNat(45);
			EntierNat n2 = new EntierNat(50);
			EntierNat n3 = new EntierNat(2147483647);
		
			//Test addition
			EntierNat n4 = EntierNat.Somme(n1, n2);
			//EntierNat n5 = EntierNat.Somme(n1, n3);
			
			//Test soustraction
			//EntierNat n6 = EntierNat.Diff(n1, n2);
			
			//Test produit
			EntierNat n7 = EntierNat.Produit(n1, n3);
		}
		catch(ErrNat e){
		
			System.out.println(e);
		}
	}
}
