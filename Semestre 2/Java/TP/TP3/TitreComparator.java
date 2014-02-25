/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Tue Feb 25 10:43:54 CET 2014
*
*/

import java.util.*;

public class TitreComparator implements Comparator{

	public int compare(Object o1, Object o2){

		Document d1 = (Document) o1;
		Document d2 = (Document) o2;
		
		if(d1.equals(d2)){

			return 0;
		}
		else{

			return d1.getTitre().compareToIgnoreCase(d2.getTitre());
		}
	}
}