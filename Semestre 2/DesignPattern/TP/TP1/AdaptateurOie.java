
public class AdaptateurOie implements Cancaneur {

	private Oie oie;
	
	public AdaptateurOie(){
		
		oie = new Oie();
	}
	
	@Override
	public void cancaner() {
		
		oie.cacarder();
	}

}
