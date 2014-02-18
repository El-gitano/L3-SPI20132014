/**
* La classe BaseDocuments contient un ensemble de documents empruntés ou non avec un ensemble d'opérations sur ces données
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 11:49:24 CET 2014
*/

import java.util.*;

public class BaseDocuments 
{ 

	private String nomBase;
	private List base;

	public BaseDocuments(String nom){

		nomBase = nom;
		base = new LinkedList();
	}
	
    /** ajoute un document dans la base de documents 
    * @param d le document à ajouter 
    */ 
    public void ajoute(Document d){

    		base.add(d);
    }

    /** supprime un document de la base de documents (si il est plusieurs 
    * fois présents, une seule des occurrences est supprimée). Il 
    * importe peu que le document soit emprunté ou non au moment de sa 
    * suppression. 
    * @param d le document à supprimer 
    * @return le document supprimé, null s’il n’existe pas 
    */ 
    public Document supprime(Document d){

		int index = base.indexOf(d);

		if(index != -1){

			base.remove(index);
			return d;
		}
		else{

			return null;
		}
    }

    /** affiche tous les documents de la mediathèque (pour impression 
    * du catalogue par exemple) 
    */ 
    public void affiche(){

    		Iterator i = base.iterator();

		System.out.println("Affiche des documents de la base\n");
		
    		while(i.hasNext()){

    			System.out.println((Document)i.next());
    		}

    		System.out.println("\n");
    }

    /** indique si le document donné est disponible (non emprunté) 
    * @param d le document concerné 
    * @return true si le document donné est disponible (non emprunté) 
    * @exception NoSuchElementException si le document n’existe 
    * pas dans la mediathèque 
    */ 
    public boolean estDisponible(Document d) throws NoSuchElementException{

    		int index = base.indexOf(d);

		if(index != -1){

			if(!((Document)base.get(index)).getEmprunt()){
				
				return true;
			}
			else{

				return false;
			}
		}
		else{

			throw new NoSuchElementException("Le document demandé n'existe pas dans la base de donnée");
		}
    }

    /** permet d’emprunter un document 
    * @param d le document concerné 
    * @exception NoSuchElementException si le document n’existe 
    * pas dans la mediathèque 
    * @return true si le document donné était disponible et a pu être emprunté 
    */ 
    public boolean emprunte(Document d) throws NoSuchElementException{

    		if(estDisponible(d)){

    			((Document)base.get(base.indexOf(d))).setEmprunt(true);
    			return true;
    		}
    		else{

    			return false;
    		}
    }

    /** permet de rendre un document 
    * @param d le document concerné 
    */ 
    public void rend(Document d){

    		((Document)base.get(base.indexOf(d))).setEmprunt(false);
    }
}