/*
 * Exo 2 du td de java sur les threads
 */

import java.io

public class FilExo {

    public static void main (String args[]){

        if(args.length < 1){
            System.err.prinln("usage : java FileExo fichiersource");
            System.exit(1);
        }

        FileReader r = new FileReader(args[0]);

        BufferedReader b = new BufferedReader(r);
        String ligne = b.readLine();

        while(ligne != null){

            int pos;
            for(pos = ligne.length -1; pos > 0; pos --){
                if (!Character.isWitheSpace(ligne.character(pos))){
                    break;
                }
            }
            System.out.println(ligne.substring(0, pos+1));
            ligne = b readLine();
        }




    }
}
