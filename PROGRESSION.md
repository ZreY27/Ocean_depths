Étape 1 : Génération de Créatures Marines🔄  
. Types de créatures   
. Structure de données suggérée  
. Génération  

Étape 2 : Système d'Attaque du Plongeur✅  
. Ressources du joueur  
. Interface de combat (exemple)  
. Mécaniques de combat  

Étape 3 : Attaque des Créatures Marines✅  
. Ordre d'attaque  
. Effets spéciaux des créatures  
. Conséquences des attaques subies  
. Ordre des actions par tour  

Étape 4 : Système de Récompenses Marines✅  
. Interface de récompense (exemple)  
![img_4.png](img_4.png)
. Types de récompenses  
. Gestion d'inventaire (exemple)  

Étape 5 : Sauvegarde et Chargement🔄  
. Données à sauvegarder  
. Contraintes  
. Exemple de structure de sauvegarde  

Étape 6 : Compétences Aquatiques❌  
. Liste des compétences
. Mécaniques  

Étape 7 : Cartographie des Océans✅  
. Interface de carte  
![img.png](img.png)
. Types de zones  
![img_1.png](img_1.png)
. Mécaniques d'exploration
![img_2.png](img_2.png)
![img_3.png](img_3.png)

Bonus Possibles❌  
. Système de Progression  
. Commerce Sous-Marin  
. Défis Spéciaux  
. Amélioration Interface  

légende :   
non commencé -> ❌  
en cours -> 🔄  
terminé -> ✅


### Difficultés rencontrées : 

# Combat : 

    La première difficulté rencontrée s'est déroulé pendant l'implémentation du système de combat. Le plus dur a été de faire l'affichage. Il a fallu faire en sorte de passer en paramètres le message pour que l'affichage se fasse de manière automatique et cohérente. De ce fait, pour afficher le combat, seule une fonction est utilisée dans laquelle nous passons en paramètres, les messages à afficher.

    La seconde était l'équilibrage du jeu. Afin d'éviter que le jeu soit trop simple et court ou trop long et monotone, il a fallu trouver des mécaniques pour améliorer le système de combatet de trouver des formules pas trop complexes pour calculer les dégâts infligés, etc.

    Mention spéciale pour les dépendances circulaires : pendant le développement du système de combat, à deux reprises, des dépendances circulaires se sont créées. Pour les résoudre, nous avons dû retirer les #include responsables des dépendances circulaires pour ensuite tagger les structures importantes et puis faire des déclarations anticipées des structures pour pouvoir compiler le projet.

    
