//TD de design pattern (celui sur les menus cafèt et crêperie).


public interface Iterateur <E>{

    public boolean encore();
    public E suivant();
}

public class Plat{}

public class MenuCreperie {

    private Plat plats;

    private class IteraeurMenuCreperie implements Iterateur<Plat> {

        private int position = 0;

        public boolean encore(){

            return (position < plats.size());
        }

        public Plat suivant(){

            return plats.get(position ++);
        }
    }

    public Iterateur creerIterateur(){

        return new IterateurMenuCreperie();
    }


}

public class MenuCafet {

    private Plat plats;

        private class IteraeurMenuCafet implements Iterateur<Plat> {

            private int position = 0;

            public boolean encore(){

                return (position < plats.size() && (plats[position] != null));
            }

            public Plat suivant(){

                return plats.get(position ++);
            }
        }

        public Iterateur creerIterateur(){

            return new IterateurMenuCafet();
        }
}

public class Serveuse {

    public void afficheMenus(){

        Iterateur<Plat> itCreperie = this.menuCreperie.creerIterateur();

        Iterateur<Plat> itCafet = this.menuCafet.creerIterateur();

        afficheMenu(itCreperie);
        afficheMenu(itCafet);
    }

    private void afficheMenus(Iterateur<Plat> it){

        while(it.encore()){

            Plat p = it.suivant();
            System.out.println(p);
        }
    }
}
