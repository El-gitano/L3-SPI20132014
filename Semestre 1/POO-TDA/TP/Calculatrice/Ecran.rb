##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Dec 04 16:50:49 CET 2013
#

#L'écran se charge d'afficher les touches numériques frappées par l'utilisateur, il sert également de buffer dans les opération unaires.
class Ecran

	@ecran
	@recouvrement
	@UC

	private_class_method :new

	attr :recouvrement, true
	attr :UC, true
	attr :ecran, false
	
	def Ecran.Creer()

		new()
	end

	def initialize() #:nodoc:
	
		@ecran = "0"
		@recouvrement = true
	end

	#Concatène "unMot" au contenu de l'écran, si recouvrement est VRAI on efface l'écran et on y ajoute le contenu de "unMot"
	def ajouter(unMot)
		
		#Si le recouvrement est à VRAI on stocke le contenu de l'écran dans l'accumulateur de l'UC
		if (@recouvrement == true) then

			@UC.sauvegarde()
			effacer()
			@recouvrement = false
		end

		@ecran << unMot
	end

	#Efface le contenu de l'écran
	def effacer()

		@ecran.clear
	end

	#Affiche l'écran
	def afficheToi()

		print "Voici l'écran : #{@ecran}\n"
	end
end
