public class ErrNat extends Exception{

	protected int nb;
	
	public ErrNat(int nb){
	
		this.nb = nb;
	}
	
	public String toString(){
	
		return "Exception ErrNat, nombre passé en paramètre : " + nb;
	}
}

class ErrConst extends ErrNat{

	public ErrConst(int nb){
	
		super(nb);
	}
}

abstract class ErrOp extends ErrNat{

	protected int nb2;
	
	public ErrOp(int op1, int op2){
	
		super(op1);
		
		nb2 = op2;
	}
}

class ErrSom extends ErrOp{

	public ErrSom(int op1, int op2){
	
		super(op1, op2);
	}
	
	public String toString(){
	
		return "Exception ErrSom, tentative d'exécution de l'opération (" + nb + " + " + nb2 + ") = " + ((long)nb + nb2);
	}
}

class ErrDiff extends ErrOp{

	public ErrDiff(int op1, int op2){
	
		super(op1 , op2);
	}
	
	public String toString(){
	
		return "Exception ErrDiff, tentative d'exécution de l'opération (" + nb + " - " + nb2 + ") = " + (nb - nb2);
	}
}

class ErrProd extends ErrOp{

	public ErrProd(int op1, int op2){
	
		super(op1 , op2);
	}
	
	public String toString(){
	
		return "Exception ErrProd, tentative d'exécution de l'opération (" + nb + " * " + nb2 + ") = " + ((long)nb * nb2);
	}
}
