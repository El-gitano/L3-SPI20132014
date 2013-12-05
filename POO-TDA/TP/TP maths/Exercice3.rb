##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 13 18:25:23 CET 2013
#

=begin

Version 1

class Livre

	@numero
	@titre
	@auteur
	@nbpages
	@etat
	@disponibilite

	private_class_method :new

	def Livre.nouveau(titre, no, auteur, nbpages)

		new(titre, no, auteur, nbpages)
	end

	def initialize(titre, no, auteur, nbpages)

		@numero = no
		@titre = titre
		@auteur = auteur
		@nbpages = nbpages
		@disponibilite = true
		@etat = "ok"
	end

	attr :numero, false
	attr :titre, false
	attr :auteur, false
	attr :nbpages, false
	attr :etat, true
	attr :disponibilite, true

	def to_s
		return "Livre : Numéro = #@numero, Titre = #@titre, Auteur = #@auteur, Nombre de pages = #@nbpages"
	end
end

=end

#La classe Biliothèque nous permet de tester la classe livre à l'aide de la méthode test1
class Bibliotheque

	@tablivre

	#Ensemble de tests de consultations/modifications sur un tableau de Livres
	def test1

		#On créé les livres
		l1 = Livre.nouveau("Hello", "TPs", 308)
		l2 = Livre.nouveau("Hello2", "TPs2", 3082)
		l3 = Livre.nouveau("Hello3", "TPs3", 3083)

		print l1,"\n"
		print l2,"\n"
		print l3,"\n"

		#On les ajoutent au tableau
		@tablivre << l1 << l2 << l3

		#On modifie des champs et on effectue des affichages
		puts "On modifie la disponibilité de Hello et l'état de Hello2"

		@tablivre[0].disponibilite=false
		@tablivre[1].etat="bad"

		print @tablivre[0].disponibilite,"\n"
		print @tablivre[1].etat,"\n"

		puts "On affiche les champs un par un"

		print @tablivre[0].numero, @tablivre[0].titre, @tablivre[0].auteur, @tablivre[0].nbpages, @tablivre[0].etat, @tablivre[0].disponibilite
	end

	#La variable d'instance @tablivre est un tableau de Livres
	def initialize

		@tablivre = Array.new
	end
		
end

#La classe livre recense toutes les informations concernant l'enregistrement d'un livre pour une bibliothèque
class Livre

	#On a 6 variables d'instance qui contiennent toutes les informations nécessaires pour enregistrer un livre dans une bibliothèque
	@numero
	@titre
	@auteur
	@nbpages
	@etat
	@disponibilite

	#Cette varaible de classe va nous permettre de savoir combien de livres sont stockés dans la bibliothèque et servira également à numéroter les nouveaux livres
	@@compteurnum = -1
	
	private_class_method :new

	#Méthode de Classe créant un nouveau livre à partir d'informations entrées par l'utilisateur
	def Livre.nouveau(titre, auteur, nbpages)

		new(titre, auteur, nbpages)
	end

	#La méthode initialize incrémente à chaque nouveau livre la variable de classe @@compteurnum afin de répertorier le nombre de livres et associer un numéro unique à chaque livre
	#Elle initialise également les différents champs d'informations sur le livre à partir des informations passées en paramètre
	def initialize(titre, auteur, nbpages)

		@@compteurnum += 1

		@numero = @@compteurnum
		@titre = titre
		@auteur = auteur
		@nbpages = nbpages
		@disponibilite = true
		@etat = "ok"
	end

	attr :numero, false
	attr :titre, false
	attr :auteur, false
	attr :nbpages, false
	attr :etat, true
	attr :disponibilite, true

	#Affiche les informations d'un livre
	def to_s
		return "Livre : Numéro = #@numero, Titre = #@titre, Auteur = #@auteur, Nombre de pages = #@nbpages"
	end
end

b = Bibliotheque.new
b.test1