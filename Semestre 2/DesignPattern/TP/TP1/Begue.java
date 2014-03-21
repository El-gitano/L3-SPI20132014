
public class Begue implements Cancaneur {

	Cancaneur c;
	
	public Begue(Cancaneur c){
		
		this.c = c;
	}
	
	@Override
	public void cancaner() {
		
		System.out.println("Je bégaye");
	}

}
