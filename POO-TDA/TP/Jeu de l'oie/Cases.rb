##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 27 13:39:45 CET 2013
#

#Définit une case neutre
class Case

	#On définit les variables d'instance
	@nom
	@casesuivante
	@caseprecedente

	#On définit les modes d'accès disponibles
	attr :nom, false

	private_class_method :new
	
	#Cette méthode initialise l'instance avec les champs adéquats
	def initialiseToi(unNom, cPrec, cSuiv)

		@nom = unNom
		@caseprecedente = cPrec
		@casesuivante = cSuiv
	end

	#Affiche la variable @nom d'une instance
	def afficheToi()

		return "#{@nom}"
	end

	#Affiche la variable @nom de l'objet appelé et toutes les cases suivantes
	def afficheTout()

		print "\t"+afficheToi()+"\n"

		if(@casesuivante != nil) then
		
			@casesuivante.afficheTout()
		end
	end

	#Fait avancer un joueur vers la case suivante nCases fois
	def faitAvancer(unJoueur, nCases)

		#On est arrivé sur la case voulue
		if nCases.zero?() then
		
			traite(unJoueur)
		else
			@casesuivante.faitAvancer(unJoueur, nCases-1)		
		end
	end

	#Fait reculer un joueur vers la case précédente nCases fois
	def faitReculer(unJoueur, nCases)

		#On est arrivé sur la case voulue
		if nCases.zero?() then
		
			self.traite(unJoueur)		
		else
			@caseprecedente.faitReculer(unJoueur, nCases-1)		
		end
	end

	def traite(unJoueur)

		print "Le joueur #{unJoueur.couleur} est sur la case \""+afficheToi()+"\"\n"
		return self
	end

	#Crée une nouvelle instance de l'objet
	def Case.Creer()

		new()
	end
end

#Définit la case de départ du jeu
class CaseDepart < Case

	#Le joueur ne pouvant pas reculer à partir de la case Départ se retrouve donc sur celle-ci
	def faitReculer(unJ, nC)
		traite(unJ)
	end
end

#Définit une case qui fait perdre un joueur
class CasePerdu < Case

	def traite(unJ)
		super(unJ)
		unJ.statut(0)
	end
end

#Si le joueur arrive sur cette case il avance de @nbDeCases
class CaseAvancer < Case

	@nbdecases

	#Fait avancer le joueur du nombre de cases définit dans @nbDeCases
	def traite(unJ)
		super(unJ)
		@casesuivante.faitAvancer(unJ, @nbdecases-1)
	end

	def initialiseToi(n, p, s, nb)

		#On fait appel à la méthode d'initialisation de la classe Case pour l'initialisation "classique" puis on initialise le nombre de cases à avancer
		super(n, p, s)
		@nbdecases = nb
	end
end

#Si le joueur arrive sur cette case il recule de @nbDeCases
class CaseReculer < Case

	@nbdecases
	
	def traite(unJ)
		super(unJ)
		@caseprecedente.faitReculer(unJ, @nbdecases-1)
	end

	def initialiseToi(n, p, s, nb)

		super(n, p, s)
		@nbdecases = nb
	end
end

#Si le joueur arrive sur cette case il se place dans la case qui a le nom @enCase
class CaseAllerA < Case

	@encase

	def traite(unJ)

		super(unJ)		
		caseCourante = @encase
	end
	
	def initialiseToi(n, p, s, cd)

		super(n, p, s)
		@encase = cd
	end	
end

#Si le joueur arrive sur cette case il gagne la partie
class CaseArrivee < Case

	@lejeu

	def faitAvancer(unJ, nC)

		if nC.zero?() then
			traite(unJ)
		else
			@caseprecedente.faitReculer(unJ, nC-1)
		end
	end
	
	def traite(unJ)
	
		super(unJ)
		@lejeu.lejoueurgagnant=unJ.couleur()
		return self
	end
	
	def initialiseToi(n, p, s, j)

		super(n, p, nil)
		@lejeu = j
	end		
end