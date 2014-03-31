/*
 *TD de JAVA sur les Threads et les entrées sorties
 */

//Toujours, quand il y a un wait() et notify(), il faut le mettre dans une section synchronized

//Exercice 1

import java.lang

public class Trieur implements Runnable{

    private int nbNotify;
    private int[] t;
    private int debut, fin;
    private Trieur parent;
    
    public Trieur(int [] x){
        
        t = x;
        debut = 0;
        fin = x.length;
        parent = null;
        nbNotify = 0;
        start();
    }

    private Trieur (int[] x, int d, int f, Trieur p){

        t = x;
        debut = d;
        fin = f;
        parent = p;
        nbNotify = 0;
        start();
    }

    public void run() {

        int tmp, milieu;

        if(fin - debut < 2) {
            
            if(t[debut] > t[fin]){

                tmp = t[debut];
                t[debut] = t[fin];
                t[fin] = tmp;
            }
        }
        else {

            milieu = (debut + fin)/2;
            Trieur tri1 = new Trieur (t, debut, milieu, this);
            Trieur tri2 = new Trieur (t, milieu + 1, fin, this);

            tri1.start();
            tri2.start();
            
            synchronized (this){ 
                try {
                    while(nbNotify < 2){
                        wait();
                    }
                }
            }
            TriFusion (debut, fin);
        }

        if(parent != null){
            synchronized(this){
                parent.nbNotify++;
                parent.notifyall();
            }
        }
    }
    /*
     * Autre possibilité pour run() :
     *
    public void run() {

        int tmp, milieu;

        if(fin - debut < 2) {
            
            if(t[debut] > t[fin]){

                tmp = t[debut];
                t[debut] = t[fin];
                t[fin] = tmp;
            }
        }
        else {

            milieu = (debut + fin)/2;
            Trieur tri1 = new Trieur (t, debut, milieu, this);
            Trieur tri2 = new Trieur (t, milieu + 1, fin, this);
            
            try {
                tri1.join();
                tri2.join();
  
            TriFusion (debut, fin);
            }catch(InterruptedException e){}
        }
    }
*/
}
