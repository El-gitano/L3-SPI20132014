import java.io.*; //Amélioration : Importer seulement les modules nécessaires

/*Affichage de 0 à la fin du programme car le buffer de 8 octets n'est pas rempli, utiliser la classe Reader pour un résulat + correct*/

public class FirstProg {

	public static void main(String[] args) {
		
		/*On teste la présence de deux arguments*/
		if(args.length < 2){
		
			System.out.println("Usage : FirstProg [Phrase à afficher] [Fichier à afficher ligne par ligne]");
		
			System.exit(-1);
		}
		
		/*Le bloc try/catch est a utiliser si on ne sait pas si args contient des arguments.
		Ceci est testé en début de programme. Pour tester le catch commenter le premier test et ne pas passer d'arguments à celui-ci lors de l'appel*/
		try{
		
			System.out.println(args[0]);
		}
		catch (ArrayIndexOutOfBoundsException e){
		
			System.err.println("Erreur dans l'affichage du paramètre, tentative d'affichage de l'index " + e.getMessage() + "du tableau d'arguments");
		}
		
		/*Ouverture et affichage du fichier*/
		BufferedInputStream bis = null;
		
		try{
		
			File f = new File(args[1]);
			bis = new BufferedInputStream(new FileInputStream(f));
			byte[] buf = new byte[8]; //Buffer de lecture de 8 octets
			
			while(bis.read(buf) >= 0){

				autreMethode(new String(buf));
			}
		}
		catch (FileNotFoundException e){
		
			e.printStackTrace();
		}
		catch(IOException e){
		
			e.printStackTrace();
		}
		finally{
		
			if(bis != null){
		
				try{
				
					bis.close();
				}
				catch (IOException e){
			
					e.printStackTrace();
				}
			}
		}
	}

	/*Méthode chargée d'afficher un objet String (pour tester)*/
	private static void autreMethode(String s){
	
		System.out.println(s);
	}
}
