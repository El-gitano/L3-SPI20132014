##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Dec 04 16:50:55 CET 2013
#

#L'Unité Centrale d'une calculatrice est la partie chargée d'effectuer les calculs
class UC

	@accumulateur
	@ecran

	private_class_method :new
	private_class_method :affichePile

	attr :ecran, true
	
	def UC.Creer()

		new()
	end

	def initialize() #:nodoc:

		@accumulateur = Array.new()
	end

	#Effectue un calcul avec 2 opérandes (1 est extraite de la pile)
	def calculBinaire(uneFonction)
		
		#On effectue le calcul
		res = @accumulateur.pop.send(uneFonction.to_sym, @ecran.ecran.to_i)	
			
		#On l'affiche à l'écran et on positionne le recouvrement à VRAI
		@ecran.effacer()
		@ecran.ajouter(res.to_s)
		@ecran.recouvrement= true
		
	end

	#Permet d'effectuer un calcul sur le contenu de l'écran
	def calculUnaire(uneFonction)

		#On récupère le nombre à l'écran
		nombre = @ecran.ecran.to_i

		#On fait le calcul
		res = nombre.send(uneFonction.to_sym)
		
		#On affiche le résultat à l'écran
		@ecran.effacer()
		@ecran.ajouter(res.to_s)
		@ecran.recouvrement= true
		
	end

	#Sauvegarde le contenu de l'écran dans la pile
	def sauvegarde()

		@accumulateur.push(@ecran.ecran.to_i)
	end

	#Vide la pile de l'UC
	def vider()

		until @accumulateur.empty?()

			@accumulateur.pop()
		end
	end

	def affichePile()

		print "#{@accumulateur}\n"
	end
end
