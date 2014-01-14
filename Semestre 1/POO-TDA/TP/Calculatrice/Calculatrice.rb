##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Dec 04 16:51:11 CET 2013
#

load "UC.rb"
load "Ecran.rb"
load "Touches.rb"

#On rajouter factorielle à la classe Integer
class Integer #:nodoc:

	def fact()

		res = 1
		
		self.downto(2){|x|

			res = res*x
		}

		return res
	end
end

#L'objet calculatrice qui se démarre à l'aide de la méthode de classe lanceToi()
class Calculatrice

	@ecran
	@UC
	@listedesTouches
	
	private_class_method :new
	
	def Calculatrice.Creer()

		new()
	end

	def initialize() #:nodoc:

		#On crée l'écran et l'UC
		@ecran = Ecran.Creer()
		@UC = UC.Creer()

		#On fait le lien entre l'écran et l'UC
		@UC.ecran=@ecran
		@ecran.UC=@UC

		#On ajoute les touches
		@listedesTouches = Array.new()

		#Ajout des touches numériques
		0.upto(9){|x|

			@listedesTouches.push(ToucheNumerique.Creer(x.to_s, @ecran))
		}
	
		#Ajout des touches fonctions
		@listedesTouches.push(ToucheFonctionBinaire.Creer("+", @UC))
		@listedesTouches.push(ToucheFonctionBinaire.Creer("-", @UC))
		@listedesTouches.push(ToucheFonctionBinaire.Creer("*", @UC))
		@listedesTouches.push(ToucheFonctionBinaire.Creer("/", @UC))

		@listedesTouches.push(ToucheFonctionUnaire.Creer("fact", @UC))

		@listedesTouches.push(ToucheFonctionSpeciale.Creer("entree", @UC, @ecran))
		@listedesTouches.push(ToucheFonctionSpeciale.Creer("clear", @UC, @ecran))
		@listedesTouches.push(ToucheFonctionSpeciale.Creer("quitter", @UC, @ecran))
	end

	#Affiche toutes les touches de la calculatrice
	def afficheTouches()

		@listedesTouches.each{|x|

			x.afficheToi()
		}

		print "\n"
	end

	#Lance la calculatrice
	def lanceToi()

		while true do
		
			@ecran.afficheToi()
			print "\nVeuillez frapper une touche : "
	
			commande = gets.chomp
	
			trouve = @listedesTouches.each{|x|

				if x.valeur.eql?(commande) then
					x.traite()
				end
			}
			
		end
	end
end
