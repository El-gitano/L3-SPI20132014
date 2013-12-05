##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 13 16:56:16 CET 2013
#

#Cette classe représente un compte en banque.
#Elle est composée de trois champs
class Compte

	#3 variables d'instance
	@numero #Numero du compte
	@titulaire #Titulaire du compte
	@solde #Solde du compte

	attr :numero, false
	attr :titulaire, true
	attr :solde, false

	#Effectue un dépôt sur le compte
	def deposer(somme)

		if somme > 0 then #On vérifie que la somme passée en argument est positive
			@solde += somme
		end
	end

	#Effectue un retrait sur le compte
	def retirer(somme)

		if somme > 0 then #On vérifie que la somme passée en argument est positive
			@solde -= somme
		end
	end

	#Affichage de l'objet
	def to_s

		puts "Titulaire : "+titulaire.to_s
		puts "Numéro : "+numero.to_s
		puts "Solde : "+solde.to_s
	end

	private_class_method :new

	#Permet d'ouvrir un nouveau compte pour un client
	def Compte.ouvrir(numero, titulaire, solde)
		
		new(numero, titulaire, solde)
	end

	def initialize(numero, titulaire, solde)

		@numero = numero
		@solde = solde
		@titulaire = titulaire
	end
end

compte1 = Compte.ouvrir(1, "Anice", 12)

puts compte1.numero
puts compte1.titulaire
puts compte1.solde.to_s+"\n"

compte1.deposer(3000)
puts "Dépôt de 3000 : "+compte1.solde.to_s+"\n"

compte1.retirer(500)
puts "Retrait de 500 : "+compte1.solde.to_s+"\n"

compte1.to_s