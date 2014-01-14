##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 13 17:34:17 CET 2013
#

#Un générateur envoi des nombres de 2 à N (spécifié par l'utilisateur) puis les fait passer par des filtres afin de déterminer si ceux-ci sont premiers ou non
class Generateur

	@premierfiltre

	#Créé le premier filtre pour le générateur
	def initialize

		@premierfiltre = Filtre.valeur(2)
	end

	#Lance l'execution de l'algorithme avec la suite de nombre déterminé à partir de celui passé en paramètre
	def lanceToi(nombre)

		if nombre > 2 then #On vérifie la valeur de nombre
		
			2.upto(nombre) do |x|
				@premierfiltre.traiter(x)
			end
			
		else
			puts "Mauvais valeur"
		end

	end

	#Affiche la liste des filtres (et donc des nombres premiers calculés précedemment à l'aide de lanceToi
	def afficheToi

		@premierfiltre.afficheToi
	end

	#Affiche la valeur du premier filtre (toujour 2 dans notre cas)
	def to_s

		@premierfiltre.to_s
	end
end

#La classe Filtre se charge de déterminer si un nombre est premier pour sa valeur.
#Si ce n'est pas le cas le filtre peut alors passer le nombre au filtre suivant s'il y en a un
#En cas d'absence de filtre suivant, le nombre traité est donc un nombre premier, on l'ajout donc à la liste des filtres
class Filtre

	#2 variables d'instance, la valeur du filtre et son successeur (s'il existe)
	@valeur
	@filtresuivant

	attr :valeur, false

	private_class_method :new

	#Valeur est le constructeur de la classe Filtre
	def Filtre.valeur(nombre)

		new(nombre)
	end

	#Lorsqu'on initialise un filtre on met la valeur du filtre suivant à nil
	def initialize(nombre)

		@valeur = nombre
		@filtresuivant = nil
	end

	#Méthode d'instance chargée de déterminer si un nombre est premier pour la valeur du filtre et d'agir en conséquence (en fonction de la présence d'un filtre suivaznt ou non)
	def traiter(nombre)

		#nombre n'est pas divisible par le filtre courant
		if nombre%@valeur != 0 then

			if @filtresuivant == nil then

				@filtresuivant = Filtre.valeur(nombre)
				#puts "Le nombre "+nombre.to_s+" est ajouté à la liste des filtres"
			else
				@filtresuivant.traiter(nombre)
			end
		end
	end

	#Méthode d'instance chargé d'afficher la valeur du filtre courant ainsi que celle de ses successeurs éventuels
	def afficheToi

		puts "Valeur : "+@valeur.to_s

		if @filtresuivant != nil then

			@filtresuivant.afficheToi
		end
	end

	def to_s

		puts "{'Valeur premier filtre':'"+@valeur.to_s+"'}"
	end
end

g = Generateur.new
g.lanceToi(100)
g.afficheToi
g.to_s