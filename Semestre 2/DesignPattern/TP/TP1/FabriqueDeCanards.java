
public class FabriqueDeCanards implements FabriqueAbstraite {

	@Override
	public Cancaneur creerOie() {
		
		return new AdaptateurOie();
	}

	@Override
	public Cancaneur creerAppeau() {
		
		return new Appeau();
	}

	@Override
	public Cancaneur creerCanardEnPlastique() {
		
		return new CanardEnPlastique();
	}

	@Override
	public Cancaneur creerColvert() {
		
		return new Colvert();
	}

	@Override
	public Cancaneur creerMandarin() {
		
		return new Mandarin();
	}

	public Cancaneur ajouterBegaiement(Cancaneur c){
		
		return new Begue(c);
	}
}
