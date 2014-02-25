class EntierNat{

	private int nb;
	
	public EntierNat(int i) throws ErrConst{
	
		if(i < 0){
		
			throw new ErrConst(i);
		}
		
		nb = i;
	}
	
	public static EntierNat Somme(EntierNat n1, EntierNat n2) throws ErrSom, ErrConst{
	
		//On dépasse la taille d'un int ?
		if( ((long)n1.getN() + (long)n2.getN()) > Integer.MAX_VALUE ){
		
			throw new ErrSom(n1.getN(), n2.getN());
		}
		else{
		
			return new EntierNat(n1.getN() + n2.getN());
		}
	}
	
	public static EntierNat Diff(EntierNat n1, EntierNat n2)throws ErrDiff, ErrConst{
	
		//La différence génère une erreur ?
		if ( ((n1.getN() - n2.getN()) < 0) || ( ((long)n1.getN() - (long)n2.getN()) > Integer.MAX_VALUE)){
			
			throw new ErrDiff(n1.getN(), n2.getN());
		}
		else{
		
			return new EntierNat(n1.getN() - n2.getN());
		}
	}
	
	public static EntierNat Produit(EntierNat n1, EntierNat n2) throws ErrProd, ErrConst{
	
		//Le produit génère-t-il une erreur ?
		if( ((n1.getN() * n2.getN()) < 0) || ( ((long)n1.getN() * (long)n2.getN()) > Integer.MAX_VALUE)){
		
			throw new ErrProd(n1.getN(), n2.getN());
		}
		else{
		
			return new EntierNat(n1.getN() * n2.getN());
		}
	}
	
	public int getN(){
	
		return nb;
	}	
}
