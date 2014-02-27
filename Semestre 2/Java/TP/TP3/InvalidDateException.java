/**
* @author ANTOINE FOUCAULT
* @version 0.1 : Date : Mon Feb 17 09:50:31 CET 2014
* Exception levée lorsque des paramètres erronés sont fournis au constructeur de la classe Date
* @see Date
*/
public class InvalidDateException extends Exception{

	public InvalidDateException(){

		super();
	}
	
	public InvalidDateException(String message){

		super(message);
	}
}