public class Login {

    private String mdp;
    int nbRefus = 0;
    boolean active = true;
    Compte compte;

    public Login (Compte c, String mp){

        this.mdp = mp;
        compte = c;
    }

    public void activer(){this.active = true}
    public boolean estActive(){ return this.active;}

    public Compte getCompte(){return compte;}

    public int getNbRefus(){return nbRefus;}
    public String getmdp() {return mdp;}

}
