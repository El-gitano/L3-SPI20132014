import java.util.Iterator;

/**
 * Un système de fichier contient un ensemble de fichiers et dossier contenus dans un tableau
 * @author Antoine Foucault
 *
 */
public class SystemeFichier implements Iterable<Fichiers> {

		private Fichiers[] tabFichier;

		/**
		 * Constructeur du système à l'aide d'un tableau
		 * @param tab - Le tableau de Fichiers
		 * @see Fichiers
		 */
		public SystemeFichier(Fichiers[] tab){
			
			tabFichier = tab;
		}
		
		/**
		 * Cette méthode retourne un itérateur sur les fichiers contenus par le système
		 * @return Un itérateur sur le tableau de fichiers
		 */
		@Override
		public Iterator<Fichiers> iterator() {
			
			return new IterateurSystemeFichiers();
		}
		
		private class IterateurSystemeFichiers implements Iterator<Fichiers>{
				
			private int compteur = 0;
				
			public boolean hasNext(){
					
				return (compteur < tabFichier.length);
			}
				
			public Fichiers next(){
					
				return tabFichier[compteur++];
			}
				
			public void remove(){}
		}
}
