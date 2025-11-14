cd C:\Users\antoi\Desktop\bureau\cours\3eme_Annee\Projet_C\cmake-build-debug
chcp 65001
.\OceanDepths.exe

# Documentation et instructions

## Combat :

Le système de combat se déroule à la manière d'un RPG tour par tour. Ces tours sont définis par la vitesse des entités présentes dans le combat. La jauge d'action de chaque entité se remplit à chaque tick (itération de la boucle du jeu). La première entité atteignant le seuil de 100 points, agit. Dans le cas où le joueur ainsi que l'ennemi atteignent tout deux le seuil en même temps, celui qui a la valeur la plus grande, agira en premier. En revanche, dans le cas où tout deux dépassent le seuil en ayant la même valeur, le joueur agira toujours avant son ennemi.

Concernant le Joueur :
    À chaque tour, le joueur a le choix d'effectuer une action de combat, d'ouvrir son inventaire, d'ouvrir le bestiaire ou de fuir.
    Une action de combat est une action que peut prendre le joueur pour influer sur le combat dans le but d'infliger des dégâts ou de contrer les effets négatives (fatigue : par le repos, dégâts ennemis : par la posture défensive).

    L'attaque légère : attaque calculée à partir de l'échelle de dégâts du joueur et de son arme tout en prenant en compte la défense de la créature.

    L'attaque lourde : même chose que l'attaque légère sauf que cette attaque inflige 2,5x plus de dégâts.

    La posture défensive (Défense) : réduit la fatigue du joueur d'un seul et unique point tout en augmentant sa défense de 50% pendant 1 tour.

    Le repos : réduit la fatigue du joueur de 2 points.

    L'ouverture de l'inventaire : permet au joueur d'utiliser un item de son inventaire pour avoir une influence sur le cours du combat. (voir la partie inventaire pour avoir un détail sur les objets)

    L'ouverture du bestiaire : Recueil de savoir dans lequel est gardé toutes informations de créature déjà rencontrée ET BATTUE.

    La fuite : si la situation ne le vous permet pas de prendre part à un combat, vous pouvez toujours sélectionner l'issue la plus simple et la plus lâche... fuir. Mais attention, il se peut que vous ayez du mal à fuir une créature plus rapide que vous.

Concernant la créature (ennemie) : 

    Lors du tour de la créature, ses actions sont déterminées par une sélection aléatoire parmis 4 actions.
    
    L'attaque basique : attaque classique, infligeant des dégâts au joueur.

    L'attaque spéciale : attaque lourde, infligeant 1,5x plus de dégâts que l'attaque basique et qui peut applique un effet néfaste au joueur si la créature en a la capacité. 

    L'observation : moment de repos pour la créature qui lui permet de réduire sa fatigue de 2 points tout en gardant un oeil sur le joueur.

    La défense : de la même manière que le joueur, la créature augmente sa défense de 50% pendant 1 tour et réduit sa fatigue d'un point.

    La fuite : cas extrêmement rare d'un créature qui prend peur à la vue d'un.... d'une combinaison de plongée.
    