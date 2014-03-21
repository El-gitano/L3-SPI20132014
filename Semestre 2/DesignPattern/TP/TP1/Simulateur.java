public class Simulateur {

	public void simuler(){
		
		Cancaneur colvert = new CompteurDeCancans(new Colvert());
		Cancaneur mandarin = new CompteurDeCancans(new Mandarin());
		Cancaneur canarEnPlastique = new CompteurDeCancans(new CanardEnPlastique());
		Cancaneur appeau = new CompteurDeCancans(new Appeau());
		Cancaneur colvertBegayeur = new Begue(colvert);
		Cancaneur oie = new CompteurDeCancans(new AdaptateurOie());
		
		System.out.println("Simulateur de canard");
		
		simuler(colvert);
		simuler(mandarin);
		simuler(canarEnPlastique);
		simuler(appeau);
		simuler(colvertBegayeur);
		simuler(oie);
		
		System.out.println("Nombre de cancaneurs : " +CompteurDeCancans.getNbCancans());
		
		System.out.println("Test des fabriques (remise à 0 du nombre de cancaneurs)");
		CompteurDeCancans.setNbCancans(0);
		
		FabriqueDeCanards fca = new FabriqueDeCanards();
		FabriqueDeComptage fco = new FabriqueDeComptage();
		
		Cancaneur colvert2 = fca.creerColvert();
		Cancaneur mandarin2 = fca.creerMandarin();
		Cancaneur canarEnPlastique2 = fca.creerCanardEnPlastique();
		Cancaneur appeau2 = fca.creerAppeau();
		Cancaneur oie2 = fca.creerOie();
		
		System.out.println("Nombre de cancaneurs : " +CompteurDeCancans.getNbCancans());
		
		Cancaneur colvert3 = fco.creerColvert();
		Cancaneur mandarin3 = fco.creerMandarin();
		Cancaneur canarEnPlastique3 = fco.creerCanardEnPlastique();
		Cancaneur appeau3 = fco.creerAppeau();
		Cancaneur oie3 = fco.creerOie();
		
		System.out.println("Nombre de cancaneurs : " +CompteurDeCancans.getNbCancans());
		
		System.out.println("Test d'une troupe de cancaneurs");
		
		TroupeDeCancaneurs tc = new TroupeDeCancaneurs();
		
		tc.ajouter(colvert3);
		tc.ajouter(mandarin3);
		tc.ajouter(canarEnPlastique3);
		tc.ajouter(appeau3);
		tc.ajouter(oie3);
		
		tc.cancaner();

	}
	
	public void simuler(Cancaneur c){
		
		c.cancaner();
	}
}
