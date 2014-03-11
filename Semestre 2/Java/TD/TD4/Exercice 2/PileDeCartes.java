import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Random;

class PileDeCartes extends Tas{
	
	public void melanger(){
	
		Collections.shuffle(tas, new Random(System.nanoTime()));
	}
	
	public void vider(){
	
		tas.clear();
	}
}
