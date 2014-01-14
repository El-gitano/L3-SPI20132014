Bienvenue sur le nouveau repo GIT de la L3 SPI 2013-2014 !

# Utiliser GIT (facilement)

##Installation

* [Pour Windows]
* [Pour Mac] 
* Pour (Maître) Linux voir ci-dessous 


```Bash
sudo apt-get install git-core
```
ou encore

```Bash
sudo yum install git
```

[Pour Windows]: http://code.google.com/p/msysgit/downloads/list?q=full+installer+official+git
[Pour Mac]: http://code.google.com/p/git-osx-installer

##Configuration

Quelques étapes de configuration vous seront nécessaire pour pouvoir utiliser GIT tranquillement.

###Les couleurs

```Bash
git config --global color.diff auto
git config --global color.status auto
git config --global color.branch auto
```

###Les informations diverses

```Bash
git config --global user.name "Votre nom/pseudo"
git config --global user.email "Votre e-mail utilisé pour vous inscrire sur github"
git config --global credential.helper cache
git config --global credential.helper 'cache --timeout=3600' (garde le mot de passe en cache 1h après authentification réussie, c'est plus pratique)
```

###Ajouter le repo et rediriger les push sur le repo commun

```Bash
git remote add upstream https://github.com/El-gitano/L3-SPI20132014.git
git fetch upstream
```

##Utilisation

En seulement 4 étapes !

1.Mettre à jour le dossier partagé

```Bash
cd "Le chemin vers le dossier cloné"
git pull
```
**Rep tant que "Travail non finit"**

2.Faire un changement (travail)

3.Commiter le changement, càd mise à jour locale (Dire la mise à jour qu'on a effectué lors de nos dernières actions"
```Bash
git commit -a
```
**Fin rep**

4.Pusher votre travail (Mettre à jour le repo)
```Bash
git push
```

#That's all
![Obama](http://voyagerloin.com/wp-content/uploads/2013/08/Obama-reddit-ama-not-bad.jpg "Tu as réussi")
