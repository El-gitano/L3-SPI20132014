
public class FabriqueDeComptage implements FabriqueAbstraite {

	@Override
	public Cancaneur creerOie() {
		
		return new CompteurDeCancans(new AdaptateurOie());
	}

	@Override
	public Cancaneur creerAppeau() {
		
		return new CompteurDeCancans(new Appeau());
	}

	@Override
	public Cancaneur creerCanardEnPlastique() {
		
		return new CompteurDeCancans(new CanardEnPlastique());
	}

	@Override
	public Cancaneur creerColvert() {
		
		return new CompteurDeCancans(new Colvert());
	}

	@Override
	public Cancaneur creerMandarin() {
		
		return new CompteurDeCancans(new Mandarin());
	}
	
	public Cancaneur ajouterBegaiement(Cancaneur c){
		
		return new Begue(c);
	}
}
