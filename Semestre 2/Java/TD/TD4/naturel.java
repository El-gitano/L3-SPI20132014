//Exercice 4 : représenter une classe permettant de représenter des entiers naturel positifs ou nul.

class ErrNat extends Exception{
    protected int num;

    public ErrNat(int n){
        num = n;
    }

    public String toString(){

        return "la valeur ayant provoqué l'erreur est " + num;
    }
}

class ErrConst extends ErrNat{

    public ErrConst(int n){
        super(n);
    }
}

class ErrOp extends ErrNat{    

    public ErrConst(int n){
        super(n);
    }
}

class ErrSom extends ErrOp{

    public ErrSom (int n){
        super(n);
    }
}

class ErrDiff extends ErrOp {

    public ErrDiff(int n){
        super(n);
    }
}

class ErrProd extends ErrOp{
    
    public ErrProd(int n){
        super(n);
}

class Naturel {

    private int valeur;

    public Naturel(int i) throws ErrConst{

        if(i < 0) throws new ErrConst(i);
        n = i;
    }
    
    public int getN(){
        return valeur;
    }

    public static Naturel somme(Naturel n1, Naturel n2) throws ErrNat{

        if (((long)n1.getN() + n2.getN()) > Integer.MAX_VALUE) throw new ErrSom(n1.getN() + n2.getN());
        return (new Naturel(n1.getN() + n2.getN());
    }

    public static Naturel différence(Naturel n1, Naturel n2) throws ErrNat {

        if(((long)n1.getN() - n2.getN()) < 0) throw new ErrDiff(n1.getN() - n2.getN());
        return (new Naturel (n1.getN() - n2.getN()));
    }
    
    public static Naturel produit(Naturel n1, Naturel n3) throw new ErrNat {

        if(((long)n1.getN() * n2.getN())> Integer.MAX_VALUE) throw new ErrProd(n1.getN() * n2.getN());
        return (new Naturel(n1.getN() * n2.getN()));
    }

}
