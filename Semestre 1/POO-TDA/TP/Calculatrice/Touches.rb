##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Dec 04 16:50:41 CET 2013
#

#La classe touche est une classe abstraite qui associe à une touche le traitement d'affichage de sa valeur
class Touche #:nodoc:

	@valeur

	private_class_method :new

	attr :valeur, false

	def initialize(uneValeur) #:nodoc:

		@valeur = uneValeur
	end
		
	def traite()

		print "La touche #{@valeur} a été  frappée\n"
	end

	def afficheToi()

		print "#{@valeur} "
	end
end

#On touche numérique s'ajoute à l'écran lorsqu'elle est frappée
class ToucheNumerique < Touche

	@ecran

	def ToucheNumerique.Creer(uneValeur, unEcran)

		new(uneValeur, unEcran)
	end

	def initialize(uneValeur, unEcran) #:nodoc:

		super(uneValeur)
		@ecran = unEcran
	end
	
	def traite()

		super()
		@ecran.ajouter(@valeur)
	end
end

class ToucheFonction < Touche #:nodoc:

	@UC

	def initialize(uneValeur, unUC)

		super(uneValeur)
		@UC = unUC
	end

	def traite()

		super()
	end
end

#La touche fonction binaire effectue une opération binaire entre le sommet de la pile de l'UC et le contenu de l'écran
class ToucheFonctionBinaire < ToucheFonction

	def ToucheFonctionBinaire.Creer(uneValeur, unUC)

		new(uneValeur, unUC)
	end

	def traite()

		super()
		@UC.calculBinaire(@valeur)
	end
end

#La touche fonction unaire effectue une opération unaire avec le contenu de l'écran, le résultat est stocké à la place de l'ex contenu de l'écran
class ToucheFonctionUnaire < ToucheFonction

	def ToucheFonctionUnaire.Creer(uneValeur, unUC)

		new(uneValeur, unUC)
	end

	def traite()

		super()
		@UC.calculUnaire(@valeur)
	end
end

#Les touches fonction spéciale sont de plusieurs sortes, elles nécessitent un accès à l'écran et l'UC
class ToucheFonctionSpeciale < ToucheFonction

	@ecran
	
	def ToucheFonctionSpeciale.Creer(uneValeur, unUC, unEcran)

		new(uneValeur, unUC, unEcran)
	end

	def initialize(uneValeur, unUC, unEcran) #:nodoc:

		super(uneValeur, unUC)
		@ecran = unEcran
	end
	
	def traite()

		super()
		
		case @valeur

		when "quitter"

			puts "Fin du programme\n\n"
			exit
			
		when "clear"

			@ecran.effacer()
			@UC.vider()
			
		when "entree"

			@ecran.recouvrement= true
		else

			print "Fonctionnalité inconnue\n"
		end
	end
end