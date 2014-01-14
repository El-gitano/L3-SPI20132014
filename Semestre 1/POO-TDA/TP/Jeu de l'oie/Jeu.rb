##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 27 13:39:56 CET 2013
#

load "Joueur.rb"
load "Cases.rb"

#On a choisi de laisser aux cases le soin de déplacer le joueur afin de ne plus toucher au code du joueur.
#En effet en laissant au cases leurs traitement du joueur on s'octroie le droit de pouvoir rajouter a posteriori de nouvelles cases avec des nouveaux traitements. 
class Jeu

	@cases
	@joueurs
	@lejoueurgagnant

	attr :lejoueurgagnant, true

	private_class_method :new

	def Jeu.Creer()

		new()
	end
	
	def initialize()

		@lejoueurgagnant = nil

		#On crée les cases
		@cases = Array.new()
		
		@cases.push(CaseDepart.Creer())
		@cases.push(CaseAllerA.Creer())
		@cases.push(Case.Creer())
		@cases.push(CaseAvancer.Creer())
		@cases.push(CaseArrivee.Creer())
		
		#On initialise les cases
		(@cases[0]).initialiseToi("depart", nil, @cases[1])
		(@cases[1]).initialiseToi("aller", @cases[0], @cases[2], @cases[0])
		(@cases[2]).initialiseToi("neutre", @cases[1], @cases[3])
		(@cases[3]).initialiseToi("avancer", @cases[2], @cases[4], 3)
		(@cases[4]).initialiseToi("arrivee", @cases[3], nil, self)

		#On crée/initialise les joueurs
		@joueurs = Array.new()
		@joueurs << Joueur.Nouveau("jaune", @cases[0]) << Joueur.Nouveau("vert", @cases[0])
	end

	def afficheToi()

		print "Joueurs :","\n\n"

		@joueurs.each{ |j|

			print "\t\t#{j.couleur}","\n"
		}

		print "\nPlateau de jeu :", "\n\n"

		(@cases[0]).afficheTout()

		return self
	end

	def lanceToi()

		until(@lejoueurgagnant != nil) || tousElimines?() do

			@joueurs.each{ |j|

				if j.estElimine?() == true then

					print "Le joueur #{j.couleur} est éliminé et ne joue donc pas\n"
									
				elsif @lejoueurgagnant == nil
				
					j.joue()
					print "Le joueur #{j.couleur} a finit son tour et est sur la case \"#{j.case.nom}\"\n"
				end
			}
		end

		if @lejoueurgagnant == nil then

			print "\nTous les joueurs sont éliminés\n\n"
		else
		
			print "\nLe joueur gagnant est : #{@lejoueurgagnant}\n\n"
		end
	end

	def tousElimines?()

		@joueurs.each{ |j|

			if !j.estElimine?() then

				return false
			end
		}

		return true
	end
end