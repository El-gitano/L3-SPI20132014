##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 27 13:41:59 CET 2013
#

class Joueur

	@case
	@statut
	@couleur

	attr :statut, true
	attr :couleur, false
	attr :case, true

	private_class_method :new
	
	def Joueur.Nouveau(uneCouleur, unDepart)

		new(uneCouleur, unDepart)
	end
	
	#Méthode qui retour vrai si le joueur est éliminé, faux sinon
	def estElimine?

		if @statut == 0 then
			return true
		else
			return false
		end		
	end

	#Méthode chargée de faire avancer le joueur d'un nombre définit par le tirage des dés et qui effectue l'action associé à la case d'arrivée
	def joue()

		#On tire les dés
		nbAvancer = tireLesDes()
		print "\nLe joueur #{@couleur} sur la case \"#{@case.nom}\" a tiré le nombre ", nbAvancer,"\n"
		
		#On modifie la case du joueur
		@case = @case.faitAvancer(self, nbAvancer)
	end

	#Méthode chargée de retourner un tirage pseudo-aléatoire entre 1 et 6
	def tireLesDes()

		#Rand avec un paramètre X de type int retourne un nombre entre 0 et X-1 (compris)
		return (1 + rand(6)) + (1+ rand(6))
	end

	def initialize(uneCouleur, uneCase)

		#On initialise nos variables d'instances qui nécessitent les paramètres
		@couleur = uneCouleur
		@case = uneCase
		
		#On met le statut du joueur à "en jeu"
		@statut = 1
	end
end
