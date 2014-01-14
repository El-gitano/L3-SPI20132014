##
# Auteur ANTOINE FOUCAULT
# Version 0.1 : Date : Wed Nov 13 19:23:12 CET 2013
#

class Integer

	
	#Méthode ajoutée à la classe Integer permettant de générer une liste des diviseurs de l'instance
	def listeDesDiviseurs

		#On déclare nos variables locales
		tab = Array.new
		
		self.downto(1) do |x|
			
			if self%x == 0 then
				
				tab.push(x)
			end
		end

		return tab
	end

	#Méthode ajoutée à la classe Integer permettant de générer une liste des non diviseurs de l'instance
	def listeDesNonsDiviseurs

		#On déclare nos variables locales
		tab = Array.new
		
		self.downto(1) do |x|

			if self%x != 0 then
				
				tab.push(x)
			end
		end

		return tab
	end

	def rapDivNonDiv

		#On calcule les sommes des numérateur et diviseurs
		num = self.listeDesDiviseurs.inject(:+)-self
		den = self.listeDesNonsDiviseurs.inject(:+)

		NR.simplifier(num, den)
	end
end

class NR

	@numerateur
	@denominateur

	attr :numerateur, false
	attr :denominateur, false

	private_class_method :new
	
	#Méthode de classe permettant de générer une instance de NR avec un numérateur et un dénominateur (passés en paramètres) les plus petits possibles
	def NR.simplifier(num, den)

		if num.eql?(den) then
		
			new(num, den)
		
		elsif den != 0 then

			ttab = Array.new
			ttab << num.listeDesDiviseurs << den.listeDesDiviseurs

			commun = ttab.inject(&:&)

			divmax = commun.max

			new(num/divmax, den/divmax)

		else

			puts "Impossible de créer un nombre rationnel avec le dénominateur nul !"
		end		
	end

	def ajouter(a)

		tab = [@denominateur, a.denominateur]

		#Si les deux frac. ont le même dénominateur
		if @denominateur.eql?(a.denominateur) then

			NR.simplifier(@numerateur + a.numerateur, @denominateur)

		#Sinon on essaie de mettre les deux fractions au même dénominateur
		elsif tab.max.listeDesDiviseurs.include?(tab.min) then

			coeff = tab.max/tab.min

			if @denominateur > a.denominateur then

				NR.simplifier(@numerateur + (a.denominateur*coeff), @denominateur)
			else
				NR.simplifier((@numerateur * coeff) + a.denominateur, a.denominateur)
			end

		#On ne peut pas effectuer le calcul
		else

			puts "Impossible de trouver un diviseur commun pour les dénominateurs des deux nombres rationnels"
		end
	end

	def soustraire(s)

		tab = [@denominateur, s.denominateur]

		#Si les deux frac. ont le même dénominateur
		if @denominateur.eql?(s.denominateur) then

			NR.simplifier(@numerateur - s.numerateur, @denominateur)

		#Sinon on essaie de mettre les deux fractions au même dénominateur
		elsif tab.max.listeDesDiviseurs.include?(tab.min) then

			coeff = tab.max/tab.min

			if @denominateur > s.denominateur then

				NR.simplifier(@numerateur - (s.denominateur*coeff), @denominateur)
			else
				NR.simplifier((@numerateur * coeff) - s.denominateur, s.denominateur)
			end

		#On ne peut pas effectuer le calcul
		else

			puts "Impossible de trouver un diviseur commun pour les dénominateurs des deux nombres rationnels"
		end
	end
	
	def multiplier(m)

		NR.Simplifier(@numerateur * m.numerateur, @denominateur * m.denominateur)
	end

	def diviser(d)

		num = @numerateur * d.denominateur
		den = @denominateur * d.numerateur
		NR.simplifier(num, den)
	end
	
	def initialize(num, den)

		@numerateur = num
		@denominateur = den
	end

	def to_s

		if @numerateur == @denominateur then

			return 1.to_s

		elsif @denominateur == 1 then

			return @numerateur.to_s

		else

			return "#@numerateur/#@denominateur"
		end
	end
end

puts "\n\tTest de la classe Integer"
puts "\t==========================="
print "Les diviseurs de 6	= "
p 6.listeDesDiviseurs()
print "Les Nons Diviseurs de 6 = "
p 6.listeDesNonsDiviseurs()
print "Le rapport des deux	= "
puts 6.rapDivNonDiv()

puts "\n\tTest de la classe NR"
puts "\t======================\n"

a=NR.simplifier(6, 9)
b=NR.simplifier(5, 3)
c=NR.simplifier(15, 18)
d=NR.simplifier(5, 20)
z=NR.simplifier(5, 1)

puts "Z = #{z}"
puts "(#{a}) + (#{b}) = #{e=a.ajouter(b)}"
puts "(#{e}) - (#{c}) = #{f=e.soustraire(c)}"
puts "(#{f}) / (#{d}) = #{g=f.diviser(d)}"
puts "(#{e}) + (#{e}) = #{e.ajouter(e)}"
puts "(#{e}) / (#{e}) = #{e.diviser(e)}"